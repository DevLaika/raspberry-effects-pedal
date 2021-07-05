#ifndef INTERFACE_H
#define INTERFACE_H

#include "effect.h"

class Interface : public Object
{
public:
  static Interface *current;
  std::string title;
  Interface *parent;
  virtual std::string get() = 0;
  virtual void up() = 0;
  virtual void down() = 0;
  virtual void select() = 0;
  virtual void back() = 0;
};

#endif