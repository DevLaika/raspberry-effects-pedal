#include "chain.h"

Chain::Chain(Effect *_effects[], int _length)
{

  length = _length;
  for (uint8_t i = 0; i < _length; i++)
  {
    effects[i] = _effects[i];
  }
};
int Chain::eval(int input_signal)
{
  if (enabled)
  {
    for (uint8_t i = 0; i < length; i++)
    {
      input_signal = effects[i]->eval(input_signal);
    }
  }
  return input_signal;
};
std::string Chain::serialize()
{
  std::stringstream stream;
  stream << "chain"
         << "\n"
         << pedalconfig::indent("effects");
  for (int i = 0; i < length; i++)
  {
    stream << "\n"
           << pedalconfig::indent(pedalconfig::indent(effects[i]->serialize()));
  }
  return stream.str();
}

ChainFactory::ChainFactory()
{
  registerFactory("chain", this);
};
Chain *ChainFactory::create(std::string config, std::string address)
{
  std::string effects_config = pedalconfig::get_body_by_head(config, "effects");

  std::vector<std::string> effect_configs_vector = pedalconfig::get_vector_of_values_by_head(effects_config, "\\S+");
  Effect *effects[MAX_CHAIN_LENGTH];
  for (uint8_t i = 0; i < effect_configs_vector.size() && i < MAX_CHAIN_LENGTH; i++)
  {
    effects[i] = (Chain *)Factory::create(effect_configs_vector.at(i), address + ".effects[" + std::to_string(i) + "].");
  }

  Chain *chain = new Chain(effects, effect_configs_vector.size());
  registerEffect(address, chain);
  return chain;
};
static ChainFactory global_ChainFactory;