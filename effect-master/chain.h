#ifndef CHAIN_H
#define CHAIN_H

#define MAX_CHAIN_LENGTH 16

#include "effect.h"
#include <sstream>

class Chain : public Effect
{
public:
  Effect *effects[MAX_CHAIN_LENGTH];
  Chain(Effect *_effects[], int _length);
  int eval(int input_signal);
  std::string serialize();

private:
  int length;
};

class ChainFactory : Factory
{
public:
  ChainFactory();
  Chain *create(std::string config, std::string address);
};

#endif