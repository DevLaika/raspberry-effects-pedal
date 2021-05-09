#include "lowpass.h"

Lowpass::Lowpass(int _smoothing_value)
{
  smoothing_value = _smoothing_value;
}

/* LOWPASS MATH

  ISSUE: LOWPASS MATH DOES NOT TAKE SAMPLE RATE INTO ACCOUT, THIS MEANS SOUND MIGHT VARY ACCORDING TO CPU USAGE

  with x as input signal, y as output signal, and smoothing_value beween 0 and 1
  y[n] = y[n-1] - smoothing_value * (y[n-1]-x[n])

  with x as input signal, y as output signal, and smoothing_value beween 0 and MAX_INPUT_VALUE
  y[n] = y[n-1] - smoothing_value/MAX_INPUT_VALUE * (y[n-1]-x[n])

 */
int Lowpass::eval(int input_signal)
{
  if (enabled)
  {
    input_signal = previous_input_signal - (smoothing_value / MAX_INPUT_VALUE) * (double)(previous_input_signal - input_signal);
  }
  previous_input_signal = input_signal;
  return input_signal;
};
int *Lowpass::getPointerTo(std::string target)
{
  if (target == "smoothing_value")
  {
    return &smoothing_value;
  }
  std::cout << "[ERR] \"" << target << "\" is not a valid value target for \"Lowpass\"!" << std::endl;
  abort();
};
std::string Lowpass::serialize()
{
  std::stringstream stream;
  stream << "lowpass"
         << "\n"
         << pedalconfig::indent("smoothing_value") << "\n"
         << pedalconfig::indent(pedalconfig::indent(std::to_string(smoothing_value)));
  return stream.str();
}

LowpassFactory::LowpassFactory()
{
  registerFactory("lowpass", this);
};
Lowpass *LowpassFactory::create(std::string config, std::string address)
{
  std::string smoothing_value_config = pedalconfig::get_body_by_head(config, "smoothing_value");

  Lowpass *lowpass = new Lowpass(std::stoi(smoothing_value_config));
  registerEffect(address, lowpass);
  return lowpass;
};
static LowpassFactory global_LowPassFactory;