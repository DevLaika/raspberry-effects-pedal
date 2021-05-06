#include "pedal.h"

Pedal::Pedal(Effect *_effect, Button *_buttons[MAX_BUTTONS], int _amnt_buttons, Interface *_interface)
{
  effect = _effect;
  amnt_buttons = _amnt_buttons;
  for (uint8_t i = 0; i < amnt_buttons && i < MAX_BUTTONS; i++)
  {
    buttons[i] = _buttons[i];
  }
  interface = _interface;
};
std::string Pedal::serialize()
{
  std::stringstream stream;
  stream << "pedal" << std::endl
         << pedalconfig::indent("effect") << std::endl
         << pedalconfig::indent(pedalconfig::indent(effect->serialize())) << std::endl
         << pedalconfig::indent("buttons") << std::endl;
  for (int i = 0; i < amnt_buttons; i++)
  {
    stream << pedalconfig::indent(pedalconfig::indent(buttons[i]->serialize())) << std::endl;
  }
  stream << pedalconfig::indent("interface") << std::endl
         << pedalconfig::indent(pedalconfig::indent(interface->serialize()));
  return stream.str();
};

Pedal *PedalFactory::create(std::string config, std::string address)
{
  std::string effect_config = pedalconfig::get_body_by_head(config, "effect");
  Effect *effect = (Effect *)Factory::create(effect_config, address + ".effect.");

  std::string buttons_config = pedalconfig::get_body_by_head(config, "buttons");
  std::vector<std::string> button_configs_vector = pedalconfig::get_vector_of_values_by_head(buttons_config, "chain");
  Button *buttons[MAX_BUTTONS];
  for (uint8_t i = 0; i < button_configs_vector.size(); i++)
  {
    buttons[i] = (Button *)Factory::create(button_configs_vector.at(i), address + ".buttons[" + std::to_string(i) + "].");
  }

  std::string interface_config = pedalconfig::get_body_by_head(config, "interface");
  Interface *interface = (Interface *)Factory::create(interface_config, address + ".interface.");
  interface->current = interface;

  Pedal *pedal = new Pedal(effect, buttons, button_configs_vector.size(), interface);
  return pedal;
};
PedalFactory::PedalFactory()
{
  registerFactory("pedal", this);
};
static PedalFactory global_pedalFactory;