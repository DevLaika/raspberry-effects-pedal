#include <iostream>
#include <string>
#include <fstream>
#include <pigpio.h>
#include "effect-master/effect.h"
#include "effect-master/pedal.h"

#define PIN_PWM_PWM0 12 //  RaspberryPi PWM0 GPIO Pin
#define PIN_PWM_PWM1 13 //  RaspberryPi PWM1 GPIO Pin

#define PIN_SPI_MISO 9
#define PIN_SPI_MOSI 10
#define PIN_SPI_SCLK 11
#define PIN_SPI_CE0 8
#define PIN_SPI_CE1

char buf[2] = {0, 0};

int spiHandle;

void setup()
{
  if (gpioInitialise() < 0)
  {
    gpioTerminate();
    if (gpioInitialise() < 0)
    {
      std::cout << "[ERR] pigpio failed to initialise!" << std::endl
                << "    | This might be because you've forgotten to run this command as root." << std::endl
                << "    | Try running as root, e.g. precede the command with \"sudo\"."
                << std::endl;
      abort();
    }
  }
  std::cout << "[INF] pigpio library initialisation was successful!" << std::endl;
  if (gpioHardwarePWM(PIN_PWM_PWM0, 19230769, 0) || gpioHardwarePWM(PIN_PWM_PWM1, 19230769, 0))
  {
    std::cout << "[ERR] PWM pins failed to initialise!" << std::endl
              << "    | Are they defined correctly?" << std::endl;
    abort();
  }
  std::cout << "[INF] PWM initialisation was successful!" << std::endl
            << "    | Set PWM frequencies are:" << std::endl
            << "    | PWM0 on pin " << PIN_PWM_PWM0 << ": " << gpioGetPWMfrequency(PIN_PWM_PWM0) << "Hz." << std::endl
            << "    | PWM1 on pin " << PIN_PWM_PWM1 << ": " << gpioGetPWMfrequency(PIN_PWM_PWM1) << "Hz." << std::endl;
  if (gpioSetPWMrange(PIN_PWM_PWM0, 63) < 0 || gpioSetPWMrange(PIN_PWM_PWM1, 63) < 0)
  {
    std::cout << "[ERR] PWM pins failed to set their range!" << std::endl;
    abort();
  }
  std::cout << "[INF] PWM pins have set their ranges successfully!" << std::endl
            << "    | Set PWM ranges are:" << std::endl
            << "    | PWM0 on pin " << PIN_PWM_PWM0 << ": " << gpioGetPWMrealRange(PIN_PWM_PWM0) << "." << std::endl
            << "    | PWM1 on pin " << PIN_PWM_PWM1 << ": " << gpioGetPWMrealRange(PIN_PWM_PWM1) << "." << std::endl;
  spiHandle = spiOpen(0, 4000000, 0b0000000000000011000000);
  if (spiHandle < 0)
  {
    std::cout << "[ERR] SPI failed to open!" << std::endl
              << "    | Is your SPI configuration correct?";
  }
}

int main()
{

  setup();

  std::ifstream ifs("conf.pedal");
  std::string config((std::istreambuf_iterator<char>(ifs)),
                     (std::istreambuf_iterator<char>()));

  Factory *factory = new Factory();
  Pedal *pedal = (Pedal *)factory->create(config, "");
  std::cout << "serial" << std::endl;
  std::cout << pedal->serialize() << std::endl;

  while (true)
  {
    // bcm2835_spi_transfernb(mosi, miso, 3);
    if (spiRead(spiHandle, buf, 12) < 0)
    {
      std::cout << "[WAR] Failed to read SPI data!" << std::endl
                << "    | Is your SPI handle set up correctly?";
    }
    int input_signal = ((buf[1] & 0x0F) << 8) | buf[0];
    // PIGPIO : spiXfer(...)

    // int output_signal = pedal->effect->eval(input_signal);
    // bcm2835_pwm_set_data(1, output_signal & 0x3F);
    // bcm2835_pwm_set_data(0, output_signal >> 6);
    // PIGPIO : gpioHardwarePWM(...) SPECIFY THE PIN RATHER THAN THE CHANNEL!!

    int in;
    int out;
    in = 10;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 20;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 30;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 40;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 50;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    pedal->buttons[0]->pressed = true;
    pedal->buttons[0]->eval();
    std::cout << pedal->interface->current->get() << std::endl;
    pedal->interface->current->select();
    std::cout << pedal->interface->current->get() << std::endl;

    in = 15;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 25;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 35;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 45;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    in = 55;
    out = pedal->effect->eval(in);
    std::cout << "in " << in << " ,out " << out << "\n";

    break;
  }

  std::cout << "[INF] End of \"main()\"" << std::endl;
  return 0;
};
