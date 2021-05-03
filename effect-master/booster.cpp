#include "booster.h"

Booster::Booster(int _booster_value)
{
  booster_value = _booster_value;
};
int Booster::eval(int input_signal)
{
  input_signal = (int)((double)(input_signal) * (double)((double)booster_value / (double)LEVEL_MAX));
  return input_signal;
};
int *Booster::getPointerTo(std::string target)
{
  if (target == "booster_value")
  {
    return &booster_value;
  }
  std::cout << "[ERROR] \"" << target << "\" is not a valid value target for \"Booster\"!" << std::endl;
  abort();
}

BoosterFactory::BoosterFactory()
{
  registerFactory("booster", this);
};
Booster *BoosterFactory::create(std::string config, std::string address)
{
  std::string booster_value_config = pedalconfig::get_body_by_head(config, "booster_value");

  Booster *booster = new Booster(std::stoi(booster_value_config));
  registerEffect(address, booster);
  return booster;
};
static BoosterFactory global_BoosterFactory;
