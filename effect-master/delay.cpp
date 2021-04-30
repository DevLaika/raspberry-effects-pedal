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

DelayFactory::DelayFactory()
{
  registerFactory("delay", this);
};
Delay *DelayFactory::create(std::string config, std::string address)
{
  Delay *delay = new Delay(std::stoi(config));
  registerEffect(address, delay);
  return delay;
};
static DelayFactory global_DelayFactory;
