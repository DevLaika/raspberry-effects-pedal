#ifndef BUTTON_H
#define BUTTON_H

#include "effect.h"

enum states
{
  idle,
  press,
  hold,
  release,
  amt_states
};

class Button : public Object
{
public:
  Button(std::function<void()> *actions[amt_states]);
  void eval();
  void act();
  bool pressed = false;
  std::string serialize();

private:
  states state = idle;
  bool pressed_previous = false;
  std::function<void()> *actions[amt_states];
};

class ButtonFactory : public Factory
{
public:
  ButtonFactory();
  Button *create(std::string config, std::string address);
};
#endif