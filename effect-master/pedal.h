#ifndef PEDAL_H
#define PEDAL_H

#include <iostream>
#include <string>
#include <map>
#include <regex>

#include "effect.h"
#include "button.h"
#include "interface.h"

#define LEVEL_MIN 0
#define LEVEL_MID 2047
#define LEVEL_MAX 4095
#define BUTTON_AMNT 4

class Pedal : public Effect
{
public:
  Pedal(Effect *effect, Button *buttons[BUTTON_AMNT], Interface *interface);
  Effect *effect;
  Button *buttons[BUTTON_AMNT];
  Interface *interface;
  int eval(int input_signal);
};

class PedalFactory : public Factory
{
public:
  PedalFactory();
  Pedal *create(std::string config, std::string address);
};

#endif