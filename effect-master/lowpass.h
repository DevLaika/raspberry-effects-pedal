#ifndef LOWPASS_H
#define LOWPASS_H

#include "effect.h"

#define MAX_INPUT_VALUE 127

class Lowpass : public Effect
{
public:
  Lowpass(int _smoothing_value);
  int eval(int input_signal);
  int *getPointerTo(std::string target);
  std::string serialize();
  int smoothing_value = 0;

private:
  int previous_input_signal = LEVEL_MID;
};

class LowpassFactory : Factory
{
public:
  LowpassFactory();
  Lowpass *create(std::string config, std::string address);
};

#endif