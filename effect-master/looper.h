#ifndef LOOPER_H
#define LOOPER_H

#include "effect.h"

#define MAX_RECORD_LENGTH 100000

class Looper : public Effect
{
public:
  bool isRecording = true;
  Looper();
  int eval(int input_signal);
  void triggerAction(std::string action);

private:
  int buffer[MAX_RECORD_LENGTH];
  int counter = 0;
  int length = 0;
};

class LooperFactory : Factory
{
public:
  LooperFactory();
  Looper *create(std::string config, std::string address);
};

#endif