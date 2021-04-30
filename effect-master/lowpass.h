#ifndef LOWPASS_H
#define LOWPASS_H

#include "effect.h"

#define MAX_INPUT_VALUE 127

class LowPass : public Effect
{
public:
  LowPass(int _smoothing_value);
  int eval(int input_signal);
  int *getPointerTo(std::string target);
  int smoothing_value = 0;

private:
  int previous_input_signal = LEVEL_MID;
};

class LowPassFactory : Factory
{
public:
  LowPassFactory();
  LowPass *create(std::string config, std::string address);
};

#endif