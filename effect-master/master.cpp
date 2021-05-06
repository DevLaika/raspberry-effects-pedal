#include "master.h"

Master::Master(Chain *_chains[], int _length, Chain *_masterChain)
{
  length = _length;
  if (_masterChain != nullptr)
    masterChain = _masterChain;
  for (uint8_t i = 0; i < length; i++)
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
    for (uint8_t i = 1; i < length; i++)
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
std::string Master::serialize()
{
  return "PLACEHOLDER!!!";
}

MasterFactory::MasterFactory()
{
  registerFactory("master", this);
};
Master *MasterFactory::create(std::string config, std::string address)
{
  std::string chains_config = pedalconfig::get_body_by_head(config, "chains");
  std::string masterchain_config = pedalconfig::get_body_by_head(config, "masterchain");

  // Sepperate chains config into sepperate instances of a chain config
  std::vector<std::string> chain_configs_vector = pedalconfig::get_vector_of_values_by_head(chains_config, "chain");

  Chain *chains[MAX_CHAIN_LENGTH];
  for (uint8_t i = 0; i < chain_configs_vector.size(); i++)
  {
    chains[i] = (Chain *)Factory::create(chain_configs_vector.at(i), address + ".chains[" + std::to_string(i) + "].");
  }

  Chain *masterchain = (Chain *)Factory::create(masterchain_config, address + ".masterchain.");

  Master *master = new Master(chains, chain_configs_vector.size(), masterchain);
  registerEffect(address, master);
  return master;
};
static MasterFactory global_MasterFactory;
