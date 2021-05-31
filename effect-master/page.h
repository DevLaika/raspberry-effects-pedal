#ifndef PAGE_H
#define PAGE_H

#include "interface.h"

class Page : public Interface
{
public:
  Page(std::string title, int *value);
  std::string get();
  void up();
  void down();
  void select();
  void back();
  std::string serialize();

private:
  int *value;
};

class PageFactory : public Factory
{
public:
  PageFactory();
  Page *create(std::string config, std::string address);
};

#endif