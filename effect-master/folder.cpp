#include "folder.h"

Folder::Folder(std::string _title, Interface *_interfaces[], int _size)
{
  title = _title;
  size = _size;
  for (uint8_t i = 0; i < size; i++)
  {
    interfaces[i] = _interfaces[i];
  }
  parent = this;
}
std::string Folder::get()
{
  return title + "\n" + interfaces[selected]->title;
}

void Folder::up()
{
  selected = (selected + 1) % size;
}
void Folder::down()
{
  selected = (selected - 1) % size;
}
void Folder::select()
{
  current = interfaces[selected];
}
void Folder::back()
{
  current = parent;
}

std::string Folder::serialize()
{
  std::stringstream stream;
  stream << "folder"
         << "\n"
         << pedalconfig::indent("title") << "\n"
         << pedalconfig::indent(pedalconfig::indent(title)) << "\n"
         << pedalconfig::indent("interfaces");
  for (int i = 0; i < size; i++)
  {
    stream << "\n"
           << pedalconfig::indent(pedalconfig::indent(interfaces[i]->serialize()));
  }
  return stream.str();
}

FolderFactory::FolderFactory()
{
  registerFactory("folder", this);
}
Folder *FolderFactory::create(std::string config, std::string address)
{
  std::string title_config = pedalconfig::get_body_by_head(config, "title");
  std::string interfaces_config = pedalconfig::get_body_by_head(config, "interfaces");

  std::vector<std::string> interface_configs_vector = pedalconfig::get_vector_of_values_by_head(interfaces_config, "\\S+");

  Interface *interfaces[MAX_INTERFACES];
  for (uint8_t i = 0; i < interface_configs_vector.size(); i++)
  {
    interfaces[i] = (Interface *)Factory::create(interface_configs_vector.at(i), address + ".interfaces[" + std::to_string(i) + "].");
  }

  Folder *folder = new Folder(title_config, interfaces, interface_configs_vector.size());
  for (uint8_t i = 0; i < interface_configs_vector.size(); i++)
  {
    interfaces[i]->parent = folder;
  }
  return folder;
}

static FolderFactory global_FolderFactory;