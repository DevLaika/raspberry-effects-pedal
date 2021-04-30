#ifndef FUZZ_H
#define FUZZ_H

#include "effect.h"

class Fuzz : public Effect
{
public:
  Fuzz(int fuzz_value);
  int eval(int input_signal);
  void setValue(int new_fuzz_value);
  int getPointerTo();
  int fuzz_value = 0;
};

class FuzzFactory : Factory
{
public:
  FuzzFactory();
  Fuzz *create(std::string config, std::string address);
};

#endif