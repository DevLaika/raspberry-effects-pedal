#ifndef FOLDER_H
#define FOLDER_H

#include "interface.h"

#define MAX_INTERFACES 16

class Folder : public Interface
{
public:
  Folder(std::string title, Interface *interfaces[], int size);
  Interface *interfaces[MAX_INTERFACES];
  void triggerAction(std::string action);
  Interface *parent;

private:
  int selected = 0;
  int size = 0;
};

class FolderFactory : public Factory
{
public:
  FolderFactory();
  Folder *create(std::string config, std::string address);
};

#endif