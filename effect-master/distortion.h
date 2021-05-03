#ifndef DISTORTION_H
#define DISTORTION_H

#include "effect.h"

class Distortion : public Effect
{
public:
  int distortion_value = 0;
  Distortion(int distortion_value);
  int eval(int input_signal);
  int *getPointerTo(std::string target);
};

class DistortionFactory : Factory
{
public:
  DistortionFactory();
  Distortion *create(std::string config, std::string address);
};

#endif