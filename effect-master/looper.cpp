#include "looper.h"

Looper::Looper(){
    // std::cout << "I am the Looper constructor\n";
};
void Looper::triggerAction(std::string action)
{
  if (action == "startstop")
  {
    if (isRecording) // End of recording
    {
      length = counter; // Set length of recording to current counter
    }
    counter = 0;                // Play/recoded head back to beginning
    isRecording = !isRecording; // Toggle whether or not it is recording
    return;
  }
  std::cout << "[WARNING] \"" << action << "\" is not a valid action for \"looper\"!" << std::endl;
};
int Looper::eval(int input_signal)
{
  // std::cout << "The looper eval was triggered\n";
  if (enabled)
  {
    // std::cout << "i am enabled\n";
    if (isRecording == true)
    { //start recording
      // std::cout << "and im recording\n";

      buffer[counter] = input_signal;
      counter++;
      //if(DelayCounter >= Delay_Depth) DelayCounter = 0;
    }
    else
    { //bypass mode
      // std::cout << "and im playing back\n";

      input_signal = (buffer[counter] + input_signal) >> 1;
      counter++;
      if (counter > length)
        counter = 0;
    }
  }
  return input_signal;
};

LooperFactory::LooperFactory()
{
  registerFactory("looper", this);
};
Looper *LooperFactory::create(std::string config, std::string address)
{
  Looper *looper = new Looper();
  registerEffect(address, looper);
  return looper;
};
static LooperFactory global_LooperFactory;