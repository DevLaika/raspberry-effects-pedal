#include "master.h"

Master::Master(Chain *_chains[MAX_CHAINS], int _length, Chain *_masterchain)
{
  length = _length;
  for (uint8_t i = 0; i < length && i < MAX_CHAINS; i++)
  {
    chains[i] = _chains[i];
  }
  masterchain = _masterchain;
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
    for (uint8_t i = 1; i < length; i++)
    {
      output_signal =
          (output_signal + chains[i]->eval(input_signal)) >> 1;
    }
  }
  if (masterchain != nullptr)
  {
    output_signal = masterchain->eval(output_signal);
  }
  return output_signal;
};
std::string Master::serialize()
{
  std::stringstream stream;
  stream << "master"
         << "\n"
         << pedalconfig::indent("chains") << "\n";
  for (int i = 0; i < length; i++)
  {
    stream << pedalconfig::indent(pedalconfig::indent(chains[i]->serialize())) << "\n";
  }
  stream << pedalconfig::indent("masterchain") << "\n"
         << pedalconfig::indent(pedalconfig::indent(masterchain->serialize()));
  return stream.str();
}

MasterFactory::MasterFactory()
{
  registerFactory("master", this);
};
Master *MasterFactory::create(std::string config, std::string address)
{
  std::string chains_config = pedalconfig::get_body_by_head(config, "chains");
  std::vector<std::string> chain_configs_vector = pedalconfig::get_vector_of_values_by_head(chains_config, "chain");
  Chain *chains[MAX_CHAIN_LENGTH];
  for (uint8_t i = 0; i < chain_configs_vector.size() && i < MAX_CHAIN_LENGTH; i++)
  {
    chains[i] = (Chain *)Factory::create(chain_configs_vector.at(i), address + ".chains[" + std::to_string(i) + "].");
  }

  std::string masterchain_config = pedalconfig::get_body_by_head(config, "masterchain");
  Chain *masterchain = (Chain *)Factory::create(masterchain_config, address + ".masterchain.");

  Master *master = new Master(chains, chain_configs_vector.size(), masterchain);
  registerEffect(address, master);
  return master;
};
static MasterFactory global_MasterFactory;
