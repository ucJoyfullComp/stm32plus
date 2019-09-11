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

  public:
    void run() {

      // initialise the ports

      GpioA<DefaultDigitalOutputFeature<6,7> > pa;
      GpioE<DigitalInputFeature<GPIO_Speed_2MHz, Gpio::PUPD_UP, 3,4> > pe;

      // lights off (this LED is active high, i.e. PD13 is a source)

      pa[6].set();
      pa[7].set();

      // create the button class with parameters

      PushButton k0(pe[4],BUTTON_PRESSED_HIGH);
      PushButton k1(pe[3],BUTTON_PRESSED_HIGH);

      // main loop
      
      bool toggle[2] = {false, false};
      bool pressed[2] = {false, false};

      for(;;) {

        // sample the button and swith the LED on (HIGH) or off (LOW)
        

        if (k0.getState()==PushButton::Pressed) {
          if (!pressed[0]) {
			  pressed[0] = true;
			  toggle[0]^=true;
		  }
        }
        else {
			pressed[0] = false;
		}
        if (toggle[0])
          pa[6].reset();
		else
          pa[6].set();

        if (k1.getState()==PushButton::Pressed) {
          if (!pressed[1]) {
			  pressed[1] = true;
			  toggle[1]^=true;
		  }
        }
        else {
			pressed[1] = false;
		}
        if (toggle[1])
          pa[7].reset();
		else
          pa[7].set();
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
