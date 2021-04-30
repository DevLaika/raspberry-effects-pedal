#include "effect.h"

void Effect::triggerAction(std::string action){};
int Effect::eval(int input_signal)
{
  // std::cout << "The base eval was triggered\n";
  return input_signal;
};
int *Effect::getPointerTo(std::string name)
{
  std::cout << "[ERROR] Cannot return pointer to value of type \"Effect\"" << std::endl;
  abort();
};

Factory::Factory(){};
std::map<std::string, Factory *> &Factory::getFactoryMap()
{
  static std::map<std::string, Factory *> factories;
  return factories;
}
std::map<std::string, Effect *> &Factory::getEffectMap()
{
  static std::map<std::string, Effect *> effects;
  return effects;
}

void Factory::registerFactory(const std::string &name, Factory *factory)
{
  Factory::getFactoryMap()[name] = factory;
};
void Factory::registerEffect(const std::string &address, Effect *effect)
{
  Factory::getEffectMap()[address] = effect;
};
Effect *Factory::create(std::string config, std::string address)
{

  std::smatch name_match;
  std::regex name_regex("^\\S+");
  std::regex_search(config, name_match, name_regex);
  std::string name = name_match.str();
  address = address + name;
  std::cout << address << std::endl;
  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  std::regex replace_begin_regex("^\\n");
  config = std::regex_replace(config, replace_name_regex, "");
  config = std::regex_replace(config, replace_spaces_regex, "\n");
  config = std::regex_replace(config, replace_begin_regex, "");

  return getFactoryMap()[name]->create(config, address);
};