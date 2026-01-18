#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

/*
Ayanat Zhu, Jan 17 updates -- Github Branch testing
This code turns LED on every other time the button is wasPressed.

Ver 2 new changes:
Renamed variables for better understanding
*/

// A function to specify delays in milliseconds
void delay_ms(int t) {
  vTaskDelay(t /portTICK_PERIOD_MS);
}

#define LED_GPIO GPIO_NUM_13
#define BUTTON GPIO_NUM_4
#define LOOP_DELAY_MS 25


bool buttonState = false;   // Button state (true = wasPressed, false = not wasPressed)
bool ledState = false;   //LED state (false = off, true = on)
bool blinkLights = false;   // blinkLights mode (off = don't blinkLights, on = blinkLights)
bool wasPressed;          // Flag to indicate a button press event


void app_main(void)
{
  gpio_reset_pin(LED_GPIO);
  gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);
  gpio_set_level(LED_GPIO, 0);
 
  gpio_reset_pin(BUTTON);
  gpio_set_direction(BUTTON, GPIO_MODE_INPUT);
  gpio_pullup_en(BUTTON);
 
  while (1) {                                 // Loop forever
    wasPressed = gpio_get_level(BUTTON) == 0;     // Input active low button
   
    if (!buttonState && wasPressed) {                  // Released button, is now wasPressed
      buttonState = true;                           // Remember button is wasPressed  
    }
   
    if (buttonState && !wasPressed) {                  // Pressed button, is now released
      blinkLights = !blinkLights;                        // Toggle LED state  
      buttonState = false;                          // Remember button is released
    }
   
    if (blinkLights) {                            //if blink mode is set to on
      //blink
      if (!ledState) {                         //if led was off
        gpio_set_level(LED_GPIO, 1);        //turn LED on
        ledState = !ledState;                  // indicate that LED was turned on
        delay_ms(125);
      } else {                              //if led was on
        gpio_set_level(LED_GPIO, 0);        //turn LED off
        ledState = !ledState;                  // indicate that LED was turned off
        delay_ms(125);
      }
    } else {                                //if blink mode is set to off
      gpio_set_level(LED_GPIO, blinkLights);       // LED turns off
    }
    delay_ms(LOOP_DELAY_MS);
  }
}