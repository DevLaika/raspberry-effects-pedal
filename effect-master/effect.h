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

class Object
{
public:
  virtual void triggerAction(std::string action);
  virtual std::string serialize();
};

class Effect : public Object
{
public:
  bool enabled = true;
  virtual int *getPointerTo(std::string name);
  virtual int eval(int input);
};

class Factory
{
public:
  Factory();
  virtual Object *create(std::string config, std::string address);

  static void registerEffect(const std::string &address, Effect *effect);
  static std::map<std::string, Effect *> &getEffectMap();

protected:
  static void registerFactory(const std::string &name, Factory *factory);
  static std::map<std::string, Factory *> &getFactoryMap();
};

#endif