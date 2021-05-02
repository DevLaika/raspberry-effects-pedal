#ifndef EFFECT_H
#define EFFECT_H

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include "util.h"

#define LEVEL_MIN 0
#define LEVEL_MID 2047
#define LEVEL_MAX 4095

class Effect
{
public:
  bool enabled = true;
  virtual int *getPointerTo(std::string name);
  virtual void triggerAction(std::string action);
  virtual int eval(int input);
};
class Factory
{
public:
  Factory();
  static void registerFactory(const std::string &name, Factory *factory);
  static void registerEffect(const std::string &address, Effect *effect);
  virtual Effect *create(std::string config, std::string address);
  static std::map<std::string, Effect *> &getEffectMap();

protected:
  static std::map<std::string, Factory *> &getFactoryMap();
};

#endif