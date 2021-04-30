#include "octaver.h"

Octaver::Octaver(int _octaver_type)
{
  octaver_type = _octaver_type;
};
int Octaver::eval(int input_signal)
{
  if (enabled)
  {
    //// I DONT UNDERSTAND THIS CODE!!!!!??????
    buffer[write] = input_signal;

    write++;
    if (write >= DELAY_DEPTH)
      write = 0;

    input_signal = buffer[read];

    if (octaver_type == 2)
      read = read + 2;
    if (octaver_type == 1)
      read = read + 1;
    if (octaver_type == 0)
    {
      divider++;
      if (divider >= 2)
      {
        read = read + 1;
        divider = 0;
      }
    }

    if (read >= DELAY_DEPTH)
      read = 0;
  }
  return input_signal;
};

OctaverFactory::OctaverFactory()
{
  registerFactory("octaver", this);
};
Octaver *OctaverFactory::create(std::string config, std::string address)
{
  Octaver *octaver = new Octaver(std::stoi(config));
  registerEffect(address, octaver);
  return octaver;
};
static OctaverFactory global_OctaverFactory;
