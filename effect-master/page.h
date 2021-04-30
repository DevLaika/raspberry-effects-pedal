#ifndef PAGE_H
#define PAGE_H

#include "interface.h"

class Page : public Interface
{
public:
  Page(std::string title, Interface *parent, int *value);
  void triggerAction(std::string action);

private:
  int *value;
  Interface *parent;
};

class PageFactory : Factory
{
public:
  PageFactory();
  Page *create(std::string config, std::string address);
};

#endif