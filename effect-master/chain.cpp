#include "chain.h"

Chain::Chain(Effect *_effects[], int _length)
{
  // std::cout << "I am the Chain constructor\n"
  //           << "The chain has a length of: " << _length << "\n";

  length = _length;
  for (int i = 0; i < _length; i++)
  {
    effects[i] = _effects[i];
  }
};
int Chain::eval(int input_signal)
{
  // std::cout << "The chain eval was triggered\n";
  if (enabled)
  {
    for (uint8_t i = 0; i < length; i++)
    {
      input_signal = effects[i]->eval(input_signal);
    }
  }
  return input_signal;
};

ChainFactory::ChainFactory()
{
  registerFactory("chain", this);
};
Chain *ChainFactory::create(std::string config, std::string address)
{
  std::regex effects_regex("(^|\\n)effects(\n( {2})+\\S+)*");
  std::smatch effects_match;
  std::regex_search(config, effects_match, effects_regex);
  std::string effects_config = effects_match.str();

  std::regex replace_begin_regex("^\\n");
  effects_config = std::regex_replace(effects_config, replace_begin_regex, "");

  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  // std::regex replace_begin_regex("^\\n"); IS ALREDY DEFINED
  effects_config = std::regex_replace(effects_config, replace_name_regex, "");
  effects_config = std::regex_replace(effects_config, replace_spaces_regex, "\n");
  effects_config = std::regex_replace(effects_config, replace_begin_regex, "");

  std::regex effect_regex("(^|\\n)\\S+(\n( {2})+\\S+)*");
  std::sregex_iterator it(effects_config.begin(), effects_config.end(), effect_regex);
  std::sregex_iterator end;

  Effect *effects[MAX_CHAIN_LENGTH];
  int i = 0;
  while (it != end)
  {
    std::string effect_config = it->str();

    effect_config = std::regex_replace(effect_config, replace_begin_regex, "");
    std::cout << effect_config << std::endl;
    effects[i] = (Effect *)Factory::create(effect_config, address + ".effects[" + std::to_string(i) + "].");
    i++;
    it++;
  }
  // std::cout << "Amount of effects in chain: " << i << std::endl;
  Chain *chain = new Chain(effects, i);
  registerEffect(address, chain);
  return chain;
};
static ChainFactory global_ChainFactory;