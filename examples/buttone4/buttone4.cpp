/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"
#include "config/button.h"


using namespace stm32plus;


/**
 * Auto-repeating button demo that doesn't use interrupts
 *
 * This demo assumes that you have a button on PA0 and an
 * LED on PD13. Hold down the button and the LED will
 * flash to indicate the presses. The default
 * configuration of PA0, PD13 and a LOW state when
 * pressed is correct for the STM32F4DISCOVERY board.
 *
 * If you are using this example on the F1VL or F0 discovery board then
 * you can replace "GpioD<DefaultDigitalOutputFeature<13> > pd;" with
 * "GpioC<DefaultDigitalOutputFeature<8> > pc;" and also each occurrence
 * of "pd[13]" with "pc[8]" to flash the blue LED on board the discovery.
 *
 * Compatible MCU:
 *   STM32F0
 *   STM32F1
 *   STM32F4
 *
 * Tested on devices:
 *   STM32F042F6P6
 *   STM32F051R8T6
 *   STM32F100RBT6
 *   STM32F103ZET6
 *   STM32F407VGT6
 */

class Button {

  protected:

    static const bool BUTTON_PRESSED_HIGH  = false;   // false = LOW when pressed, true = HIGH when pressed
    static const uint32_t INITIAL_DELAY_MS = 600;
    static const uint32_t REPEAT_DELAY_MS  = 150;

  public:
    void run() {

      // initialise the ports

      GpioC<DefaultDigitalOutputFeature<4> > pc;
      GpioE<DigitalInputFeature<GPIO_Speed_50MHz, Gpio::PUPD_UP, 4> > pe;

      // lights off (this LED is active high, i.e. PD13 is a source)

      pc[4].reset();

      // create the button class with parameters

      AutoRepeatPushButton button(pe[4],BUTTON_PRESSED_HIGH,INITIAL_DELAY_MS,REPEAT_DELAY_MS);

      // main loop

      for(;;) {

        // sample the button and swith the LED on (HIGH) or off (LOW)

        if(button.getState()==PushButton::Pressed) {

          // switch the LED on for 10ms

          pc[4].set();
          MillisecondTimer::delay(10);
        }
        else
          pc[4].reset();
      }
    }
};


/*
 * Main entry point
 */

int main() {

  // set up SysTick at 1ms resolution
  MillisecondTimer::initialise();

  Button button;
  button.run();

  // not reached
  return 0;
}
