#include "button.h"

Button::Button(Effect *_targets[amt_states], std::string _actions[amt_states])
{
  for (int i = 0; i < amt_states; i++)
  {
    targets[i] = _targets[i];
    actions[i] = _actions[i];
  }
  act();
};

int Button::eval(int input_signal)
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
  return input_signal;
};

void Button::act()
{
  std::cout << "state: " << state << std::endl;
  std::cout << "action: " << actions[state] << std::endl;
  std::cout << "target: " << targets[state] << std::endl;
  if (actions[state] == "")
    return;
  if (actions[state] == "toggle")
  {
    targets[state]->enabled = !targets[state]->enabled;
    return;
  }
  targets[state]->triggerAction(actions[state]);
}

Button *ButtonFactory::create(std::string config, std::string address)
{
  std::regex idle_regex("(^|\\n)idle(\n( {2})+\\S+)*"), press_regex("(^|\\n)press(\n( {2})+\\S+)*"), hold_regex("(^|\\n)hold(\n( {2})+\\S+)*"), release_regex("(^|\\n)release(\n( {2})+\\S+)*");
  std::smatch idle_match, press_match, hold_match, release_match;
  std::regex_search(config, idle_match, idle_regex);
  std::regex_search(config, press_match, press_regex);
  std::regex_search(config, hold_match, hold_regex);
  std::regex_search(config, release_match, release_regex);

  std::string idle_config, press_config, hold_config, release_config;
  idle_config = idle_match.str();
  press_config = press_match.str();
  hold_config = hold_match.str();
  release_config = release_match.str();

  std::regex replace_name_regex("^\\S+\\n?"), replace_spaces_regex("(^|\\n) {2}"), replace_begin_regex("^\\n");
  idle_config = std::regex_replace(idle_config, replace_begin_regex, "");
  idle_config = std::regex_replace(idle_config, replace_name_regex, "");
  idle_config = std::regex_replace(idle_config, replace_spaces_regex, "\n");
  idle_config = std::regex_replace(idle_config, replace_begin_regex, "");

  press_config = std::regex_replace(press_config, replace_begin_regex, "");
  press_config = std::regex_replace(press_config, replace_name_regex, "");
  press_config = std::regex_replace(press_config, replace_spaces_regex, "\n");
  press_config = std::regex_replace(press_config, replace_begin_regex, "");

  hold_config = std::regex_replace(hold_config, replace_begin_regex, "");
  hold_config = std::regex_replace(hold_config, replace_name_regex, "");
  hold_config = std::regex_replace(hold_config, replace_spaces_regex, "\n");
  hold_config = std::regex_replace(hold_config, replace_begin_regex, "");

  release_config = std::regex_replace(release_config, replace_begin_regex, "");
  release_config = std::regex_replace(release_config, replace_name_regex, "");
  release_config = std::regex_replace(release_config, replace_spaces_regex, "\n");
  release_config = std::regex_replace(release_config, replace_begin_regex, "");

  std::smatch state_address_matches[amt_states];
  std::regex address_regex("^\\S+");
  std::regex_search(idle_config, state_address_matches[idle], address_regex);
  std::regex_search(press_config, state_address_matches[press], address_regex);
  std::regex_search(hold_config, state_address_matches[hold], address_regex);
  std::regex_search(release_config, state_address_matches[release], address_regex);

  Effect *targets[amt_states];
  Effect *dummy = new Effect();

  for (int i = 0; i < amt_states; i++)
  {
    targets[i] = (state_address_matches[i].str() != "") ? getEffectMap()[state_address_matches[i].str()] : dummy;
    if (targets[i] == 0)
    {
      std::cout << "[ERROR] You fucked up an address in the button configuration!" << std::endl;
      std::cout << "Address: \"" << state_address_matches[i].str() << "\" is not a valid address!" << std::endl;
      abort();
    }
  }

  idle_config = std::regex_replace(idle_config, replace_name_regex, "");
  idle_config = std::regex_replace(idle_config, replace_spaces_regex, "\n");
  idle_config = std::regex_replace(idle_config, replace_begin_regex, "");

  press_config = std::regex_replace(press_config, replace_name_regex, "");
  press_config = std::regex_replace(press_config, replace_spaces_regex, "\n");
  press_config = std::regex_replace(press_config, replace_begin_regex, "");

  hold_config = std::regex_replace(hold_config, replace_name_regex, "");
  hold_config = std::regex_replace(hold_config, replace_spaces_regex, "\n");
  hold_config = std::regex_replace(hold_config, replace_begin_regex, "");

  release_config = std::regex_replace(release_config, replace_name_regex, "");
  release_config = std::regex_replace(release_config, replace_spaces_regex, "\n");
  release_config = std::regex_replace(release_config, replace_begin_regex, "");

  std::string actions[] = {idle_config, press_config, hold_config, release_config};

  Button *button = new Button(targets, actions);
  registerEffect(address, button);
  return button;
}

ButtonFactory::ButtonFactory()
{
  registerFactory("button", this);
};

static ButtonFactory global_ButtonFactory;