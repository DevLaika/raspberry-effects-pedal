#ifndef PAGE_H
#define PAGE_H

#include "interface.h"

class Page : public Interface
{
public:
  Page(std::string title, int *value);
  void triggerAction(std::string action);
  Interface *parent;

private:
  int *value;
};

class PageFactory : Factory
{
public:
  PageFactory();
  Page *create(std::string config, std::string address);
};

#endif