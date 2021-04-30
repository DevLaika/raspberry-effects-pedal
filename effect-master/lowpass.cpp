#include "lowpass.h"

LowPass::LowPass(int _smoothing_value)
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
int LowPass::eval(int input_signal)
{
  if (enabled)
  {
    input_signal = previous_input_signal - (smoothing_value / MAX_INPUT_VALUE) * (double)(previous_input_signal - input_signal);
  }
  previous_input_signal = input_signal;
  return input_signal;
};
int *LowPass::getPointerTo(std::string target)
{
  if (target == "smoothing_value")
  {
    return &smoothing_value;
  }
  std::cout << "[ERROR] \"" << target << "\" is not a valid value target for lowpass!" << std::endl;
  abort();
};

LowPassFactory::LowPassFactory()
{
  registerFactory("lowpass", this);
};
LowPass *LowPassFactory::create(std::string config, std::string address)
{
  std::regex smoothing_value_regex("(^|\\n)smoothing_value(\n( {2})+\\S+)*");
  std::smatch smoothing_value_match;
  std::regex_search(config, smoothing_value_match, smoothing_value_regex);
  std::string smoothing_value_config = smoothing_value_match.str();

  std::regex replace_begin_regex("^\\n");
  smoothing_value_config = std::regex_replace(smoothing_value_config, replace_begin_regex, "");

  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  // std::regex replace_begin_regex("^\\n"); IS ALREDY DEFINED
  smoothing_value_config = std::regex_replace(smoothing_value_config, replace_name_regex, "");
  smoothing_value_config = std::regex_replace(smoothing_value_config, replace_spaces_regex, "\n");
  smoothing_value_config = std::regex_replace(smoothing_value_config, replace_begin_regex, "");

  LowPass *lowpass = new LowPass(std::stoi(smoothing_value_config));
  registerEffect(address, lowpass);
  return lowpass;
};
static LowPassFactory global_LowPassFactory;