#ifndef OCTAVER_H
#define OCTAVER_H

#include "effect.h"

#ifndef MAX_RECORD_LENGTH
#define MAX_RECORD_LENGTH 100000
#endif // !MAX_RECORD_LENGTH

#ifndef DELAY_DEPTH
#define DELAY_DEPTH 500000
#endif // !DELAY_DEPTH

class Octaver : public Effect
{
public:
  int octaver_type = 0;
  Octaver(int octaver_type);
  int eval(int input_signal);

private:
  int buffer[MAX_RECORD_LENGTH];
  int divider = 0;
  int read = 0;
  int write = 0;
};

class OctaverFactory : Factory
{
public:
  OctaverFactory();
  Octaver *create(std::string config, std::string address);
};

#endif