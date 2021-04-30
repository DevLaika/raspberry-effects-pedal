#ifndef BUTTON_H
#define BUTTON_H

#include "effect.h"
#define CLOCKS_PER_MILLISEC CLOCKS_PER_SEC / 1000

enum states
{
  idle,
  press,
  hold,
  release,
  amt_states
};

class Button : public Effect
{
public:
  Button(Effect *targets[amt_states], std::string actions[amt_states]);
  int eval(int input_signal);
  void act();
  bool pressed = false;

protected:
private:
  states state = idle;
  bool pressed_previous = false;
  Effect *targets[amt_states];
  std::string actions[amt_states];
};

class ButtonFactory : public Factory
{
public:
  ButtonFactory();
  Button *create(std::string config, std::string address);
};
#endif