#ifndef PEDAL_H
#define PEDAL_H

#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <sstream>

#include "effect.h"
#include "button.h"
#include "interface.h"

#define LEVEL_MIN 0
#define LEVEL_MID 2047
#define LEVEL_MAX 4095
#define MAX_BUTTONS 4

class Pedal : public Object
{
public:
  Pedal(Effect *effect, Button *buttons[MAX_BUTTONS], int amnt_buttons, Interface *interface);
  std::string serialize();
  Effect *effect;
  Button *buttons[MAX_BUTTONS];
  Interface *interface;

private:
  int amnt_buttons;
};

class PedalFactory : public Factory
{
public:
  PedalFactory();
  Pedal *create(std::string config, std::string address);
};

#endif