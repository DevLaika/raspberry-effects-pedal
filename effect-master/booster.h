#ifndef BOOSTER_H
#define BOOSTER_H

#include "effect.h"

class Booster : public Effect
{
public:
  int booster_value = 0;
  Booster(int booster_value);
  int eval(int input_signal);
  int *getPointerTo(std::string target);
};

class BoosterFactory : public Factory
{
public:
  BoosterFactory();
  Booster *create(std::string config, std::string address);
};

#endif