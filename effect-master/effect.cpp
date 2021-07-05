#include "effect.h"

std::string Object::serialize()
{
  return "/* PLACEHOLDER */";
};
int Effect::eval(int input_signal)
{
  return input_signal;
};
int *Effect::getPointerTo(std::string name)
{
  std::cout << "[ERR] Cannot return pointer to value of type \"Effect\"" << std::endl;
  abort();
};
void Effect::toggle()
{
  enabled = !enabled;
}

Factory::Factory(){};
std::unordered_map<std::string, Factory *> &Factory::getFactoryMap()
{
  static std::unordered_map<std::string, Factory *> factories;
  return factories;
}
std::unordered_map<std::string, Effect *> &Factory::getEffectInstanceMap()
{
  static std::unordered_map<std::string, Effect *> effects;
  return effects;
}
std::unordered_map<Effect *, std::string> &Factory::getEffectAddressMap()
{
  static std::unordered_map<Effect *, std::string> addresses;
  return addresses;
}
std::unordered_map<std::function<void()> *, std::string> &Factory::getFunctionNameMap()
{
  static std::unordered_map<std::function<void()> *, std::string> functions;
  return functions;
};
std::unordered_map<std::string, std::function<void()> *> &Factory::getFunctionPointerMap()
{
  static std::unordered_map<std::string, std::function<void()> *> names;
  return names;
};
std::unordered_map<int *, std::string> &Factory::getValueNameMap()
{
  static std::unordered_map<int *, std::string> names;
  return names;
};
std::unordered_map<std::string, int *> &Factory::getValuePointerMap()
{
  static std::unordered_map<std::string, int *> values;
  return values;
};
void Factory::registerValue(const std::string &name, int *value)
{
  Factory::getValuePointerMap()[name] = value;
  Factory::getValueNameMap()[value] = name;
}
void Factory::registerFunction(const std::string &name, std::function<void()> *function)
{
  Factory::getFunctionPointerMap()[name] = function;
  Factory::getFunctionNameMap()[function] = name;
}
void Factory::registerFactory(const std::string &name, Factory *factory)
{
  Factory::getFactoryMap()[name] = factory;
};
void Factory::registerEffect(const std::string &address, Effect *effect)
{
  Factory::getEffectInstanceMap()[address] = effect;
  Factory::getEffectAddressMap()[effect] = address;
};

Object *Factory::create(std::string config, std::string address)
{
  std::string name = pedalconfig::get_first_head_value(config);
  std::string effect_config = pedalconfig::get_first_body_value(config);
  address = address + name;

  return getFactoryMap()[name]->create(effect_config, address);
};