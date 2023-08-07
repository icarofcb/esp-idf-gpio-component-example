#pragma once

#include "driver/gpio.h"
#include "esp_event.h"

ESP_EVENT_DECLARE_BASE(INPUT_EVENTS);

class GpioBase {
 protected:
  gpio_num_t _pin;
  bool _active_low = false;
};  // GpioBase Class

class GpioInput : public GpioBase {
 private:
  esp_err_t _init(const gpio_num_t pin, const bool activeLow);
  bool _event_handler_set = false;
  static bool _interrupt_service_installed;

 public:
  GpioInput(const gpio_num_t pin, const bool activeLow);
  GpioInput(const gpio_num_t pin);
  GpioInput(void);
  esp_err_t init(const gpio_num_t pin, const bool activeLow);
  esp_err_t init(const gpio_num_t pin);
  int read(void);

  esp_err_t enablePullup(void);
  esp_err_t disablePullup(void);
  esp_err_t enablePulldown(void);
  esp_err_t disablePulldown(void);
  esp_err_t enablePullupPulldown(void);
  esp_err_t disablePullupPulldown(void);

  esp_err_t enableInterrupt(gpio_int_type_t int_type);
  esp_err_t setEventHandler(esp_event_handler_t Gpio_e_h);
  static void IRAM_ATTR gpio_isr_callback(void* arg);
};  // GpioInput Class

class GpioOutput : public GpioBase {
 private:
  int _level = 0;
  esp_err_t _init(const gpio_num_t pin, const bool activeLow);

 public:
  GpioOutput(const gpio_num_t pin, const bool activeLow);
  GpioOutput(const gpio_num_t pin);
  GpioOutput(void);
  esp_err_t init(const gpio_num_t pin, const bool activeLow);
  esp_err_t init(const gpio_num_t pin);
  esp_err_t on(void);
  esp_err_t off(void);
  esp_err_t toggle(void);
  esp_err_t setLevel(int level);
};  // GpioOutput Class