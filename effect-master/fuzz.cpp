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
int *Fuzz::getPointerTo(std::string target)
{
  if (target == "fuzz_value")
  {
    return &fuzz_value;
  }
  std::cout << "[ERR] \"" << target << "\" is not a valid value target for \"Fuzz\"!" << std::endl;
  abort();
}

FuzzFactory::FuzzFactory()
{
  registerFactory("fuzz", this);
};
Fuzz *FuzzFactory::create(std::string config, std::string address)
{
  std::string full_value_config = pedalconfig::get_body_by_head(config, "fuzz_value");
  Fuzz *fuzz = new Fuzz(std::stoi(full_value_config));
  registerEffect(address, fuzz);
  return fuzz;
};
static FuzzFactory global_FuzzFactory;
