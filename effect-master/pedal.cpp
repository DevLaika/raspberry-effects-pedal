#include "pedal.h"

Pedal::Pedal(Effect *_effect, Button *_buttons[BUTTON_AMNT], Interface *_interface)
{
  effect = _effect;
  for (int i = 0; i < BUTTON_AMNT; i++)
  {
    buttons[i] = _buttons[i];
  }
  interface = _interface;
}

int Pedal::eval(int input_signal)
{
  if (!enabled)
  {
    return LEVEL_MID;
  }
  return effect->eval(input_signal);
};
Pedal *PedalFactory::create(std::string config, std::string address)
{
  std::string effect_config = pedalconfig::get_body_by_head(config, "effect");
  Effect *effect = Factory::create(effect_config, address + ".effect.");

  std::string buttons_config = pedalconfig::get_body_by_head(config, "buttons");
  std::regex button_regex("(?!\\n)button(\n( {2})+\\S+)*");
  std::sregex_iterator it(buttons_config.begin(), buttons_config.end(), button_regex);
  std::sregex_iterator end;
  Button *buttons[BUTTON_AMNT] = {};
  int i = 0;
  while (it != end && i < BUTTON_AMNT)
  {
    std::string button_config = it->str();
    buttons[i] = (Button *)Factory::create(button_config, address + ".buttons[" + std::to_string(i) + "].");
    i++;
    it++;
  }

  std::string interface_config = pedalconfig::get_body_by_head(config, "interface");
  Interface *interface = (Interface *)Factory::create(interface_config, address + ".interface.");
  interface->current = interface;
  // if need size of buttons[] plz add size to constructor <3
  Pedal *pedal = new Pedal(effect, buttons, interface);
  registerEffect(address, pedal);
  return pedal;
};
PedalFactory::PedalFactory()
{
  registerFactory("pedal", this);
};
static PedalFactory global_pedalFactory;