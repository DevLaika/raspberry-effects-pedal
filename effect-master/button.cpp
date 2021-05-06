#include "button.h"

Button::Button(Effect *_targets[amt_states], std::string _actions[amt_states])
{
  for (uint8_t i = 0; i < amt_states; i++)
  {
    targets[i] = _targets[i];
    actions[i] = _actions[i];
  }
  act();
};

void Button::eval()
{
  if (pressed_previous != pressed)
  {
    pressed_previous = pressed;
    if (pressed)
    {
      state = press;
    }
    if (!pressed)
    {
      state = release;
    }
    act();
  }
};

void Button::act()
{
  if (actions[state] == "")
    return;
  if (actions[state] == "toggle")
  {
    targets[state]->enabled = !targets[state]->enabled;
    return;
  }
  targets[state]->triggerAction(actions[state]);
}
std::string Button::serialize()
{
  return "HI IM SERIALISED BUTTON";
}

Button *ButtonFactory::create(std::string config, std::string address)
{

  std::string state_configs[amt_states];
  state_configs[idle] = pedalconfig::get_body_by_head(config, "idle");
  state_configs[press] = pedalconfig::get_body_by_head(config, "press");
  state_configs[hold] = pedalconfig::get_body_by_head(config, "hold");
  state_configs[release] = pedalconfig::get_body_by_head(config, "release");

  std::string actions[amt_states];
  Effect *targets[amt_states];
  Effect *dummy = new Effect();

  for (uint8_t i = 0; i < amt_states; i++)
  {
    std::string state_target_address = pedalconfig::get_first_head_value(state_configs[i]);
    targets[i] = (state_target_address != "") ? getEffectMap()[state_target_address] : dummy;
    if (targets[i] == nullptr)
    {
      std::cout << "[ERR] You fucked up an address in the button configuration!" << std::endl;
      std::cout << "address: \"" << state_target_address << "\" is not a valid address!" << std::endl;
      abort();
    }

    actions[i] = pedalconfig::get_first_body_value(state_configs[i]);
  }

  Button *button = new Button(targets, actions);
  return button;
}

ButtonFactory::ButtonFactory()
{
  registerFactory("button", this);
};

static ButtonFactory global_ButtonFactory;