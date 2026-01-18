#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

/*
Ayanat Zhu, Jan 17 updates -- Github Branch testing
This code turns LED on every other time the button is pressed.

Added new changes
*/

// A function to specify delays in milliseconds
void delay_ms(int t) {
  vTaskDelay(t /portTICK_PERIOD_MS);
}

#define LED_GPIO GPIO_NUM_13
#define BUTTON GPIO_NUM_4
#define LOOP_DELAY_MS 25


bool bstate = false;   // Button state (true = pressed, false = not pressed)
bool lstate = false;   //LED state (false = off, true = on)
bool blink = false;   // blink mode (off = don't blink, on = blink)
bool pressed;          // Flag to indicate a button press event


void app_main(void)
{
  gpio_reset_pin(LED_GPIO);
  gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(LED_GPIO, 0);
 
  gpio_reset_pin(BUTTON);
  gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
  gpio_pullup_en(BUTTON);
 
  while (1) {                                 // Loop forever
    pressed = gpio_get_level(BUTTON) == 0;     // Input active low button
   
    if (!bstate && pressed) {                  // Released button, is now pressed
      bstate = true;                           // Remember button is pressed  
    }
   
    if (bstate && !pressed) {                  // Pressed button, is now released
      blink = !blink;                        // Toggle LED state  
      bstate = false;                          // Remember button is released
    }
   
    if (blink) {                            //if blink mode is set to on
      //blink
      if (!lstate) {                         //if led was off
        gpio_set_level(LED_GPIO, 1);        //turn LED on
        lstate = !lstate;                  // indicate that LED was turned on
        delay_ms(125);
      } else {                              //if led was on
        gpio_set_level(LED_GPIO, 0);        //turn LED off
        lstate = !lstate;                  // indicate that LED was turned off
        delay_ms(125);
      }
    } else {                                //if blink mode is set to off
      gpio_set_level(LED_GPIO, blink);       // LED turns off
    }
    delay_ms(LOOP_DELAY_MS);
  }
}