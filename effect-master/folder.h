#ifndef FOLDER_H
#define FOLDER_H

#include "interface.h"

#define MAX_INTERFACES 16

class Folder : public Interface
{
public:
  Folder(std::string title, Interface *interfaces[], int size);
  Interface *interfaces[MAX_INTERFACES];
  std::string serialize();
  std::string get();
  void up();
  void down();
  void select();
  void back();

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