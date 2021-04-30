#include "page.h"

Page::Page(std::string _title, Interface *_parent, int *_value)
{
  title = _title;
  parent = _parent;
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