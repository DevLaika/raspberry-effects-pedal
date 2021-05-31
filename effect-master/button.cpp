#include "button.h"

Button::Button(std::function<void()> *_actions[amt_states])
{
  for (uint8_t i = 0; i < amt_states; i++)
  {
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
  if (actions[state])
  {
    (*actions[state])();
  }
}
std::string Button::serialize()
{
  std::stringstream stream;
  stream << "button"
         << "\n"
         << pedalconfig::indent("idle") << "\n";
  if (actions[idle])
  {
    stream << pedalconfig::indent(pedalconfig::indent(Factory::getFunctionNameMap()[actions[idle]])) << "\n";
  }
  stream << pedalconfig::indent("press") << "\n";
  if (actions[press])
  {
    stream << pedalconfig::indent(pedalconfig::indent(Factory::getFunctionNameMap()[actions[press]])) << "\n";
  }
  stream << pedalconfig::indent("hold") << "\n";
  if (actions[hold])
  {
    stream << pedalconfig::indent(pedalconfig::indent(Factory::getFunctionNameMap()[actions[hold]])) << "\n";
  }
  stream << pedalconfig::indent("release");
  if (actions[release])
  {
    stream << "\n"
           << pedalconfig::indent(pedalconfig::indent(Factory::getFunctionNameMap()[actions[release]]));
  }
  return stream.str();
}

Button *ButtonFactory::create(std::string config, std::string address)
{

  std::string state_configs[amt_states];
  state_configs[idle] = pedalconfig::get_body_by_head(config, "idle");
  state_configs[press] = pedalconfig::get_body_by_head(config, "press");
  state_configs[hold] = pedalconfig::get_body_by_head(config, "hold");
  state_configs[release] = pedalconfig::get_body_by_head(config, "release");

  std::function<void()> *actions[amt_states];

  for (uint8_t i = 0; i < amt_states; i++)
  {
    if (state_configs[i] == "")
    {
      actions[i] = nullptr;
      continue;
    }
    if (!getFunctionPointerMap().count(state_configs[i]))
    {
      std::cout << "[WAR] In \"" << address << "\": configuration of state " << std::to_string(i) << " (0=idle, 1=press, 2=hold, 3=release) \"" << state_configs[i] << "\" is invalid." << std::endl;
    }
    actions[i] = getFunctionPointerMap()[state_configs[i]];
  }

  Button *button = new Button(actions);
  return button;
}

ButtonFactory::ButtonFactory()
{
  registerFactory("button", this);
};

static ButtonFactory global_ButtonFactory;