#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <map>

#include "util.h"

class Object
{
public:
  virtual void triggerAction(std::string action);
  virtual std::string serialize();
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