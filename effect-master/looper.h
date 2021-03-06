#ifndef LOOPER_H
#define LOOPER_H

#include "effect.h"
#include <functional>

#define MAX_RECORD_LENGTH 100000

class Looper : public Effect
{
public:
  int isRecording = 127;
  Looper();
  int eval(int input_signal);
  void startstop();
  std::string serialize();

private:
  int buffer[MAX_RECORD_LENGTH];
  int counter = 0;
  int length = 0;
};

class LooperFactory : public Factory
{
public:
  LooperFactory();
  Looper *create(std::string config, std::string address);
};

#endif