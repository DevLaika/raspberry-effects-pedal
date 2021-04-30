#include "fuzz.h"

Fuzz::Fuzz(int _fuzz_value)
{
  fuzz_value = _fuzz_value;
};
int Fuzz::eval(int input_signal)
{
  if (input_signal > LEVEL_MID + fuzz_value)
    input_signal = LEVEL_MAX;
  if (input_signal < LEVEL_MID - fuzz_value)
    input_signal = LEVEL_MIN;
  return input_signal;
};
void Fuzz::setValue(int new_value)
{
  fuzz_value = new_value;
}
FuzzFactory::FuzzFactory()
{
  registerFactory("fuzz", this);
};
Fuzz *FuzzFactory::create(std::string config, std::string address)
{
  Fuzz *fuzz = new Fuzz(std::stoi(config));
  registerEffect(address, fuzz);
  return fuzz;
};
static FuzzFactory global_FuzzFactory;
