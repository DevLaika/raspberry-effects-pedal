#ifndef DELAY_H
#define DELAY_H

#include "effect.h"

#define MAX_RECORD_LENGTH 100000

class Delay : public Effect
{
public:
  int delay_depth = 0;
  Delay(int delay_depth);
  int eval(int input_signal);
  int *getPointerTo(std::string target);

private:
  int buffer[MAX_RECORD_LENGTH];
  int counter = 0;
  int length = 0;
};

class DelayFactory : Factory
{
public:
  DelayFactory();
  Delay *create(std::string config, std::string address);
};

#endif