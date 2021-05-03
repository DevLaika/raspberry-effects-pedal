#ifndef FUZZ_H
#define FUZZ_H

#include "effect.h"

class Fuzz : public Effect
{
public:
  Fuzz(int fuzz_value);
  int eval(int input_signal);
  int *getPointerTo();
  int fuzz_value = 0;
  int *getPointerTo(std::string target);
};

class FuzzFactory : Factory
{
public:
  FuzzFactory();
  Fuzz *create(std::string config, std::string address);
};

#endif