#include "looper.h"

Looper::Looper(){};
void Looper::startstop()
{
  if (isRecording != 0) // End of recording
  {
    length = counter; // Set length of recording to current counter
  }
  counter = 0;                                   // Play/recoded head back to beginning
  isRecording = ((isRecording + 1) % 128) * 127; // Toggle whether or not it is recording
};
int Looper::eval(int input_signal)
{
  if (enabled)
  {
    if (isRecording == true)
    { //start recording

      buffer[counter] = input_signal;
      counter++;
      //if(DelayCounter >= Delay_Depth) DelayCounter = 0;
    }
    else
    { //bypass mode

      input_signal = (buffer[counter] + input_signal) >> 1;
      counter++;
      if (counter > length)
        counter = 0;
    }
  }
  return input_signal;
};
std::string Looper::serialize()
{
  std::stringstream stream;
  stream << "looper";
  return stream.str();
}

LooperFactory::LooperFactory()
{
  registerFactory("looper", this);
};
Looper *LooperFactory::create(std::string config, std::string address)
{
  Looper *looper = new Looper();
  registerEffect(address, looper);
  registerValue(address + ".isRecording", &looper->isRecording);
  std::function<void()> *toggle_l_ptr = new std::function<void()>([looper]
                                                                  { looper->toggle(); });
  registerFunction(address + ".toggle()", toggle_l_ptr);
  std::function<void()> *startstop_l_ptr = new std::function<void()>([looper]
                                                                     { looper->startstop(); });
  registerFunction(address + ".startstop()", startstop_l_ptr);
  return looper;
};

static LooperFactory global_LooperFactory;
