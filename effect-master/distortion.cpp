#include "distortion.h"

Distortion::Distortion(int _distortion_value)
{
  distortion_value = _distortion_value;
};
int Distortion::eval(int input_signal)
{
  if (input_signal > LEVEL_MID + distortion_value)
    input_signal = LEVEL_MID + distortion_value;
  if (input_signal < LEVEL_MID - distortion_value)
    input_signal = LEVEL_MID - distortion_value;
  return input_signal;
};

DistortionFactory::DistortionFactory()
{
  registerFactory("distortion", this);
};
Distortion *DistortionFactory::create(std::string config, std::string address)
{
  Distortion *distortion = new Distortion(std::stoi(config));
  registerEffect(address, distortion);
  return distortion;
};
static DistortionFactory global_DistortionFactory;
