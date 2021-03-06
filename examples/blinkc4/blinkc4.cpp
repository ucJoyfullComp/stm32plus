/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013,2014 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

#include "config/stm32plus.h"
#include "config/gpio.h"
#include "config/timing.h"


using namespace stm32plus;


/**
 * This is the most basic example that uses GPIO and the
 * Systick timer to blink a LED on PG14 at 1Hz. PG14 is wired
 * to the red onboard LED D2 on the BIT Ver. 2.0 boards.
 *
 * If the STM32F4DISCOVERY board is your target then
 * change the GPIO declation to...
 *
 *  GpioD<DefaultDigitalOutputFeature<13> > pd
 *
 * ... and change 2 of "pg[14]" to "pd[13]" to blink the
 * orange led on the discovery board.
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
 *   STM32F107VCT6
 */

class Blink {

  public:

    void run() {

      // initialise the pin for output

      GpioC<DefaultDigitalOutputFeature<4> > pc;

      // loop forever switching it on and off with a 1 second
      // delay in between each cycle

      for(;;) {

        pc[4].set();
        MillisecondTimer::delay(1000);

        pc[4].reset();
        MillisecondTimer::delay(1000);
      }
    }
};


/*
 * Main entry point
 */

int main() {

  // set up SysTick at 1ms resolution
  MillisecondTimer::initialise();

  Blink blink;
  blink.run();

  // not reached
  return 0;
}
