#pragma once

#include <ctype.h>
#include <inttypes.h>
#include <string.h>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <string>

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "led_strip.h"
// GPIO assignment
#define LED_STRIP_BLINK_GPIO 38
static const char* TAG = "aguaalaser";
}

#include "cppgpio.h"

// Main class used for testing only
class Main final {
 public:
  void run(void);
  void setup(void);

  led_strip_handle_t configure_led(void);

  GpioOutput output_1{GPIO_NUM_42};
  GpioOutput output_2{GPIO_NUM_48};
  GpioOutput output_3{GPIO_NUM_41};
  GpioInput input_1{GPIO_NUM_0};
  led_strip_handle_t led_strip;

  // Event Handler for cppButton
  static void button_event_handler(void* handler_args,
                                   esp_event_base_t base,
                                   int32_t id,
                                   void* event_data);


};  // Main Class