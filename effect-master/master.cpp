#include "master.h"

Master::Master(Chain *_chains[], int _length, Chain *_masterChain)
{
  length = _length;
  if (_masterChain != nullptr)
    masterChain = _masterChain;
  for (int i = 0; i < length; i++)
  {
    chains[i] = _chains[i];
  }
};
int Master::eval(int input_signal)
{
  if (!enabled)
  {
    return input_signal;
  }
  output_signal = chains[0]->eval(input_signal);
  if (length > 1)
  {
    for (int i = 1; i < length; i++)
    {
      output_signal =
          (output_signal + chains[i]->eval(input_signal)) >> 1;
    }
  }
  if (masterChain != nullptr)
  {
    output_signal = masterChain->eval(output_signal);
  }
  return output_signal;
};

MasterFactory::MasterFactory()
{
  registerFactory("master", this);
};
Master *MasterFactory::create(std::string config, std::string address)
{
  // Sepperate config into both the chains and masterchain config
  std::regex chains_regex("(^|\\n)chains(\n( {2})+\\S+)*"),
      masterchain_regex("(^|\\n)masterchain(\n( {2})+\\S+)*");
  std::smatch chains_match, masterchain_match;
  std::regex_search(config, chains_match, chains_regex);
  std::regex_search(config, masterchain_match, masterchain_regex);
  std::string chains_config = chains_match.str();
  std::string masterchain_config = masterchain_match.str();
  // Replace the newline of either chains or masterchain config to empty, this will make the string start with either "chains" or "masterchain" instead of either "\nchain" or "\nmasterchain"
  std::regex replace_begin_regex("^\\n");
  chains_config = std::regex_replace(chains_config, replace_begin_regex, "");
  masterchain_config = std::regex_replace(masterchain_config, replace_begin_regex, "");

  // std::cout << "chains: \n"
  //           << chains_config << "\n";
  // std::cout << "masterchain: \n"
  //           << masterchain_config << "\n";

  // Remove the chains or masterchain identifier and the whitespace of all the configs
  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  // std::regex replace_begin_regex("^\\n"); IS ALREDY DEFINED
  chains_config = std::regex_replace(chains_config, replace_name_regex, "");
  chains_config = std::regex_replace(chains_config, replace_spaces_regex, "\n");
  chains_config = std::regex_replace(chains_config, replace_begin_regex, "");

  masterchain_config = std::regex_replace(masterchain_config, replace_name_regex, "");
  masterchain_config = std::regex_replace(masterchain_config, replace_spaces_regex, "\n");
  masterchain_config = std::regex_replace(masterchain_config, replace_begin_regex, "");

  // Sepperate chains config into sepperate instances of a chain config
  std::regex chain_regex("(^|\\n)chain(\n( {2})+\\S+)*");
  std::sregex_iterator it(chains_config.begin(), chains_config.end(), chain_regex);
  std::sregex_iterator end;

  Chain *chains[MAX_CHAIN_LENGTH];
  int i = 0;
  while (it != end)
  {
    std::string chain_config = it->str();
    chain_config = std::regex_replace(chain_config, replace_begin_regex, "");

    chains[i] = (Chain *)Factory::create(chain_config, address + ".chains[" + std::to_string(i) + "].");
    i++;
    it++;
  }

  Chain *masterchain = (Chain *)Factory::create(masterchain_config, address + ".masterchain.");

  Master *master = new Master(chains, i, masterchain);
  registerEffect(address, master);
  return master;
};
static MasterFactory global_MasterFactory;
