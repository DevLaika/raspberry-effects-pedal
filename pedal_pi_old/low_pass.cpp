// CC-by-www.Electrosmash.com Pedl-Pi open-source project
// low_pass.c the effect is ran through a low-pass filter, controlled using the smoothing factor 'beta'.

#include <stdio.h>
#include <bcm2835.h>

// Define Input Pins
#define PUSH1 RPI_GPIO_P1_08            //GPIO14
#define PUSH2 RPI_V2_GPIO_P1_38         //GPIO20
#define TOGGLE_SWITCH RPI_V2_GPIO_P1_32 //GPIO12
#define FOOT_SWITCH RPI_GPIO_P1_10      //GPIO15
#define LED RPI_V2_GPIO_P1_36           //GPIO16

//**** LOW-PASS EFFECT ***///
/*
  A simple implementation of a low-pass filter
  with x being the input signal,
  y the output signal,
  and ß the smoothing factor.
  y[i] := ß * x[i] + (1-ß) * y[i-1] = y[i-1] - (ß*(y[i-1] - x[i]))
*/
uint32_t lowpass(uint32_t input_signal, uint32_t previous_output_signal, float beta)
{
  return output_signal = output_signal - (beta * (output_signal - input_signal)(float))(uint32_t);
}

uint32_t read_timer = 0;

uint32_t input_signal = 0;
uint32_t output_signal = 0;

float beta = 0.025;

uint8_t FOOT_SWITCH_val;
uint8_t TOGGLE_SWITCH_val;
uint8_t PUSH1_val;
uint8_t PUSH2_val;

//main program
int main(int argc, char **argv)
{
  // Start the BCM2835 Library to access GPIO.
  if (!bcm2835_init())
  {
    printf("bcm2835_init failed. Are you running as root??\n");
    return 1;
  }

  // Start the SPI BUS.
  if (!bcm2835_spi_begin())
  {
    printf("bcm2835_spi_begin failed. Are you running as root??\n");
    return 1;
  }

  //define PWM mode
  bcm2835_gpio_fsel(18, BCM2835_GPIO_FSEL_ALT5); //PWM0 signal on GPIO18
  bcm2835_gpio_fsel(13, BCM2835_GPIO_FSEL_ALT0); //PWM1 signal on GPIO13
  bcm2835_pwm_set_clock(2);                      // Max clk frequency (19.2MHz/2 = 9.6MHz)
  bcm2835_pwm_set_mode(0, 1, 1);                 //channel 0, markspace mode, PWM enabled.
  bcm2835_pwm_set_range(0, 64);                  //channel 0, 64 is max range (6bits): 9.6MHz/64=150KHz PWM freq.
  bcm2835_pwm_set_mode(1, 1, 1);                 //channel 1, markspace mode, PWM enabled.
  bcm2835_pwm_set_range(1, 64);                  //channel 0, 64 is max range (6bits): 9.6MHz/64=150KHz PWM freq.

  //define SPI bus configuration
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);   // The default
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                // The default
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_64); // 4MHz clock with _64
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                   // The default
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);   // the default

  uint8_t mosi[10] = {0x01, 0x00, 0x00}; //12 bit ADC read channel 0.
  uint8_t miso[10] = {0};

  //Define GPIO pins configuration
  bcm2835_gpio_fsel(PUSH1, BCM2835_GPIO_FSEL_INPT);         //PUSH1 button as input
  bcm2835_gpio_fsel(PUSH2, BCM2835_GPIO_FSEL_INPT);         //PUSH2 button as input
  bcm2835_gpio_fsel(TOGGLE_SWITCH, BCM2835_GPIO_FSEL_INPT); //TOGGLE_SWITCH as input
  bcm2835_gpio_fsel(FOOT_SWITCH, BCM2835_GPIO_FSEL_INPT);   //FOOT_SWITCH as input
  bcm2835_gpio_fsel(LED, BCM2835_GPIO_FSEL_OUTP);           //LED as output

  bcm2835_gpio_set_pud(PUSH1, BCM2835_GPIO_PUD_UP);         //PUSH1 pull-up enabled
  bcm2835_gpio_set_pud(PUSH2, BCM2835_GPIO_PUD_UP);         //PUSH2 pull-up enabled
  bcm2835_gpio_set_pud(TOGGLE_SWITCH, BCM2835_GPIO_PUD_UP); //TOGGLE_SWITCH pull-up enabled
  bcm2835_gpio_set_pud(FOOT_SWITCH, BCM2835_GPIO_PUD_UP);   //FOOT_SWITCH pull-up enabled

  while (1) //Main Loop
  {
    //Read the PUSH buttons every 50000 times (0.25s) to save resources.
    read_timer++;
    if (read_timer == 50000)
    {
      read_timer = 0;
      uint8_t PUSH1_val = bcm2835_gpio_lev(PUSH1);
      uint8_t PUSH2_val = bcm2835_gpio_lev(PUSH2);
      TOGGLE_SWITCH_val = bcm2835_gpio_lev(TOGGLE_SWITCH);
      uint8_t FOOT_SWITCH_val = bcm2835_gpio_lev(FOOT_SWITCH);
      bcm2835_gpio_write(LED, !FOOT_SWITCH_val); //light the effect when the footswitch is activated.
    }

    // read 12 bits ADC, miso[0] will be empty, miso[1] and miso[2] contain the 12 bit data (half of miso[1] data will be 0 and the other half is from the ADC 0x0000XXXX. miso[2] is fully populated data from the ADC). we dont care abotu miso[3-9]
    bcm2835_spi_transfernb(mosi, miso, 3);
    /* 
      miso[1] is 8 bit, last four are the values we need, last four are always 0
      (miso[1] & 0x0F) ensures only the last four are used
      ((miso[1] & 0x0F) << 8) shift those four bits to the left by eight bits, effectively multiplying by 256 (values 0-4095 in increments of 256)
      miso[2] = LAST 8 BITS (values 0-255)
      input_signal = (values 0-4095 in increments of 256) + (values 0-255)
    */
    input_signal = ((miso[1] & 0x0F) << 8) + miso[2];

    //**** EFFECT CHAIN ***///
    output_signal = lowpass(input_signal, output_signal, beta);

    // generate output PWM signal 6 bits pwm0 is the first 6 bits (0-4095 in incements of 64), pwm1 is the last 6 bits (0-63)
    bcm2835_pwm_set_data(1, output_signal & 0x3F);
    bcm2835_pwm_set_data(0, output_signal >> 6);
  }

  //close all and exit
  bcm2835_spi_end();
  bcm2835_close();
  return 0;
}
