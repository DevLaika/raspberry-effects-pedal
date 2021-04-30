#ifndef INTERFACE_H
#define INTERFACE_H

#include "effect.h"

class Interface : public Effect
{
public:
  static Interface *current;
  std::string title;
  Interface *parent;
};

#endif