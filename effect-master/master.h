#ifndef MASTER_H
#define MASTER_H

#include "chain.h"
#include "effect.h"

#define MAX_CHAINS 16

class Master : public Effect
{
public:
  Chain *chains[MAX_CHAINS];
  Chain *masterChain = nullptr;
  Master(Chain *_chains[], int _length, Chain *_masterChain = nullptr);
  int eval(int input_signal);

private:
  int length;
  int output_signal;
};

class MasterFactory : Factory
{
public:
  MasterFactory();
  Master *create(std::string config, std::string address);
};

#endif