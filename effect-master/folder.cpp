#include "folder.h"

Folder::Folder(std::string _title, Interface *_interfaces[], int _size)
{
  title = _title;
  size = _size;
  for (int i = 0; i < size; i++)
  {
    interfaces[i] = _interfaces[i];
  }
  parent = this;
}

void Folder::triggerAction(std::string action)
{
  if (action == "add")
  {
    selected = (selected + 1) % size;
    return;
  }
  if (action == "remove")
  {
    selected = (selected - 1) % size;
    return;
  }
  if (action == "select")
  {
    current = interfaces[selected];
    return;
  }
  if (action == "back")
  {
    current = parent;
    return;
  }
  std::cout << "[WARNING] \"" << action << " is not a valid action for \"Folder\"" << std::endl;
  return;
}

FolderFactory::FolderFactory()
{
  registerFactory("folder", this);
}
Folder *FolderFactory::create(std::string config, std::string address)
{
  std::regex title_regex("(^|\\n)title(\n( {2})+\\S+)*");
  std::smatch title_match;
  std::regex_search(config, title_match, title_regex);
  std::string title_config = title_match.str();

  std::regex replace_begin_regex("^\\n");
  title_config = std::regex_replace(title_config, replace_begin_regex, "");

  std::regex replace_name_regex("^\\S+\\n?");
  std::regex replace_spaces_regex("(^|\\n) {2}");
  title_config = std::regex_replace(title_config, replace_name_regex, "");
  title_config = std::regex_replace(title_config, replace_spaces_regex, "\n");
  title_config = std::regex_replace(title_config, replace_begin_regex, "");

  std::regex interfaces_regex("(^|\\n)interfaces(\n( {2})+\\S+)*");
  std::smatch interfaces_match;
  std::regex_search(config, interfaces_match, interfaces_regex);
  std::string interfaces_config = interfaces_match.str();

  interfaces_config = std::regex_replace(interfaces_config, replace_begin_regex, "");

  interfaces_config = std::regex_replace(interfaces_config, replace_name_regex, "");
  interfaces_config = std::regex_replace(interfaces_config, replace_spaces_regex, "\n");
  interfaces_config = std::regex_replace(interfaces_config, replace_begin_regex, "");

  std::regex interface_regex("(^|\\n)\\S+(\n( {2})+\\S+)*");
  std::sregex_iterator it(interfaces_config.begin(), interfaces_config.end(), interface_regex);
  std::sregex_iterator end;

  Interface *interfaces[MAX_INTERFACES];
  int interfaces_amount = 0;
  while (it != end && interfaces_amount < MAX_INTERFACES)
  {
    std::string interface_config = it->str();
    interface_config = std::regex_replace(interface_config, replace_begin_regex, "");
    // std::cout << interface_config << std::endl;
    interfaces[interfaces_amount] = (Interface *)Factory::create(interface_config, address + ".interfaces[" + std::to_string(interfaces_amount) + "].");
    interfaces_amount++;
    it++;
  }
  Folder *folder = new Folder(title_config, interfaces, interfaces_amount);
  for (int i = 0; i < interfaces_amount; i++)
  {
    interfaces[i]->parent = folder;
  }
  return folder;
}

static FolderFactory global_FolderFactory;