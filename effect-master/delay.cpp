#include "delay.h"

Delay::Delay(int _delay_depth)
{
  delay_depth = _delay_depth;
};
int Delay::eval(int input_signal)
{
  if (enabled)
  {
    buffer[counter] = input_signal;
    counter++;
    if (counter >= delay_depth)
      counter = 0;
    input_signal = (buffer[counter] + input_signal) >> 1;
  }
  return input_signal;
};
int *Delay::getPointerTo(std::string target)
{
  if (target == "delay_depth")
  {
    return &delay_depth;
  }
  std::cout << "[ERR] \"" << target << "\" is not a valid value target for \"Delay\"!" << std::endl;
  abort();
}

DelayFactory::DelayFactory()
{
  registerFactory("delay", this);
};
Delay *DelayFactory::create(std::string config, std::string address)
{
  std::string delay_depth_config = pedalconfig::get_body_by_head(config, "delay_depth");
  Delay *delay = new Delay(std::stoi(delay_depth_config));
  registerEffect(address, delay);
  return delay;
};
static DelayFactory global_DelayFactory;
