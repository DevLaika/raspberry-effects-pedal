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
int *Distortion::getPointerTo(std::string target)
{
  if (target == "distortion_value")
  {
    return &distortion_value;
  }
  std::cout << "[ERR] \"" << target << "\" is not a valid value target for \"Distortion\"!" << std::endl;
  abort();
}

DistortionFactory::DistortionFactory()
{
  registerFactory("distortion", this);
};
Distortion *DistortionFactory::create(std::string config, std::string address)
{
  std::string distortion_value_config = pedalconfig::get_body_by_head(config, "distortion_value");
  Distortion *distortion = new Distortion(std::stoi(distortion_value_config));
  registerEffect(address, distortion);
  return distortion;
};
static DistortionFactory global_DistortionFactory;
