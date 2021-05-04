#include <iostream>
#include <string>
#include <fstream>
#include "effect-master/effect.h"
#include "effect-master/pedal.h"

// char mosi[10] = {0x01, 0x00, 0x00};
// char miso[10] = {0};

int main()
{
  std::ifstream ifs("conf.pedal");
  std::string config((std::istreambuf_iterator<char>(ifs)),
                     (std::istreambuf_iterator<char>()));

  Factory *factory = new Factory();
  Pedal *pedal = (Pedal *)factory->create(config, "");

  while (true)
  {
    // bcm2835_spi_transfernb(mosi, miso, 3);
    // int input_signal = ((miso[1] & 0x0F) << 8) + miso[2];

    // int output_signal = pedal->effect->eval(input_signal);
    // bcm2835_pwm_set_data(1, output_signal & 0x3F);
    // bcm2835_pwm_set_data(0, output_signal >> 6);

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

    break;
  }

  std::cout << "[INFO] End of \"main()\"";
  return 0;
};