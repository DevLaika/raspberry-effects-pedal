#ifndef INTERFACE_H
#define INTERFACE_H

#include "effect.h"

class Interface : public Effect
{
public:
  static Interface *current;
  std::string title;
  Interface *parent;
  virtual std::string getDisplay() = 0;
};

#endif