#include "effect.h"

void Object::triggerAction(std::string action){};
std::string Object::serialize()
{
  return "/* PLACEHOLDER */";
};
int Effect::eval(int input_signal)
{
  // std::cout << "The base eval was triggered\n";
  return input_signal;
};
int *Effect::getPointerTo(std::string name)
{
  std::cout << "[ERR] Cannot return pointer to value of type \"Effect\"" << std::endl;
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
Object *Factory::create(std::string config, std::string address)
{
  std::string name = pedalconfig::get_first_head_value(config);
  std::string effect_config = pedalconfig::get_first_body_value(config);
  address = address + name;

  return getFactoryMap()[name]->create(effect_config, address);
};