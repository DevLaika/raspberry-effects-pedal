#include "page.h"
#include "util.cpp"

Page::Page(std::string _title, int *_value)
{
  title = _title;
  value = _value;
}

void Page::triggerAction(std::string action)
{
  if (action == "add")
  {
    (*value)++;
    return;
  }
  if (action == "remove")
  {
    (*value)--;
    return;
  }
  if (action == "select")
  {
    return;
  }
  if (action == "back")
  {
    current = parent;
    return;
  }
  std::cout << "[WARNING] \"" << action << " is not a valid action for \"Page\"" << std::endl;
  return;
}

PageFactory::PageFactory()
{
  registerFactory("page", this);
}

Page *PageFactory::create(std::string config, std::string address)
{
  std::string title_config = pedalconfig::get_value_by_key(config, "title");
  std::string value_config = pedalconfig::get_value_by_key(config, "value");
  std::string target_address_config = pedalconfig::get_first_head_value(value_config);
  std::string target_value_config = pedalconfig::get_first_body_value(value_config);

  int *target_value_pointer = getEffectMap()[target_address_config]->getPointerTo(target_value_config);

  Page *page = new Page(title_config, target_value_pointer);
  return page;
}