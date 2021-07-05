#include "page.h"

Page::Page(std::string _title, int *_value)
{
  title = _title;
  value = _value;
  parent = this;
}
std::string Page::get()
{
  return title + "\n" + std::to_string(*value);
}
void Page::up()
{
  (*value)++;
}
void Page::down()
{
  (*value)--;
}
void Page::select()
{
  ;
}
void Page::back()
{
  current = parent;
}
std::string Page::serialize()
{
  std::stringstream stream;
  stream << "page"
         << "\n"
         << pedalconfig::indent("title") << "\n"
         << pedalconfig::indent(pedalconfig::indent(title)) << "\n"
         << pedalconfig::indent("value") << "\n"
         << pedalconfig::indent(pedalconfig::indent(Factory::getValueNameMap()[value]));
  return stream.str();
}

PageFactory::PageFactory()
{
  registerFactory("page", this);
}

Page *PageFactory::create(std::string config, std::string address)
{
  std::string title_config = pedalconfig::get_body_by_head(config, "title");
  std::string value_config = pedalconfig::get_body_by_head(config, "value");

  if (!getValuePointerMap().count(value_config))
  {
    std::cout << "[ERR] In \"" << address << "\": \"" << value_config << "\"does not exist!" << std::endl;
  }

  int *target_value_pointer = getValuePointerMap()[value_config];

  Page *page = new Page(title_config, target_value_pointer);
  return page;
}

static PageFactory global_PageFactory;