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

BoosterFactory::BoosterFactory()
{
  registerFactory("booster", this);
};
Booster *BoosterFactory::create(std::string config, std::string address)
{
  Booster *booster = new Booster(std::stoi(config));
  registerEffect(address, booster);
  return booster;
};
static BoosterFactory global_BoosterFactory;
