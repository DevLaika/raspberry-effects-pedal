#ifndef EFFECT_H
#define EFFECT_H

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <functional>
#include "util.h"

#define LEVEL_MIN 0
#define LEVEL_MID 2047
#define LEVEL_MAX 4095

class Object
{
public:
  virtual std::string serialize();
};

class Effect : public Object
{
public:
  bool enabled = true;
  virtual int *getPointerTo(std::string name);
  virtual int eval(int input);
  void toggle();
};

class Factory
{
public:
  Factory();
  virtual Object *create(std::string config, std::string address);

  static void registerValue(const std::string &name, int *value);
  static std::unordered_map<int *, std::string> &getValueNameMap();
  static std::unordered_map<std::string, int *> &getValuePointerMap();

  static void registerFunction(const std::string &name, std::function<void()> *function);
  static std::unordered_map<std::function<void()> *, std::string> &getFunctionNameMap();
  static std::unordered_map<std::string, std::function<void()> *> &getFunctionPointerMap();

  static void registerEffect(const std::string &address, Effect *effect);
  static std::unordered_map<std::string, Effect *> &getEffectInstanceMap();
  static std::unordered_map<Effect *, std::string> &getEffectAddressMap();

  static void registerFactory(const std::string &name, Factory *factory);
  static std::unordered_map<std::string, Factory *> &getFactoryMap();
};

#endif