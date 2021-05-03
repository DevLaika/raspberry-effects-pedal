#include <iostream>
#include <string>
#include <fstream>
#include "effect-master/effect.h"
#include "effect-master/pedal.h"
#include "effect-master/chain.h"
#include "effect-master/master.h"
#include "effect-master/looper.h"
#include "effect-master/lowpass.h"
#include "effect-master/button.h"
#include "effect-master/interface.h"

int main()
{
  std::ifstream ifs("conf.pedal");
  std::string config((std::istreambuf_iterator<char>(ifs)),
                     (std::istreambuf_iterator<char>()));

  Factory *factory = new Factory();
  Pedal *pedal;

  pedal = (Pedal *)factory->create(config, "");
  int in;
  int out;
  in = 10;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 20;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 30;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 40;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 50;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  pedal->buttons[0]->pressed = true;
  pedal->buttons[0]->eval(0);
  std::cout << pedal->interface->current->getDisplay() << std::endl;
  pedal->interface->current->triggerAction("select");
  std::cout << pedal->interface->current->getDisplay() << std::endl;

  in = 15;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 25;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 35;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 45;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  in = 55;
  out = pedal->eval(in);
  std::cout << "in " << in << " ,out " << out << "\n";

  std::cout << "FINISHED";
  return 0;
};