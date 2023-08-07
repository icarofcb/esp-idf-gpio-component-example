#include "cppgpio.h"

// Static variable initializations
bool GpioInput::_interrupt_service_installed{false};

ESP_EVENT_DEFINE_BASE(INPUT_EVENTS);

void IRAM_ATTR GpioInput::gpio_isr_callback(void* args) {
  int32_t pin = reinterpret_cast<int32_t>(args);

  esp_event_isr_post(INPUT_EVENTS, pin, nullptr, 0, nullptr);
}

esp_err_t GpioInput::_init(const gpio_num_t pin, const bool activeLow) {
  esp_err_t status{ESP_OK};

  _active_low = activeLow;
  _pin = pin;

  gpio_config_t cfg;
  cfg.pin_bit_mask = 1ULL << pin;
  cfg.mode = GPIO_MODE_INPUT;
  cfg.pull_up_en = GPIO_PULLUP_DISABLE;
  cfg.pull_down_en = GPIO_PULLDOWN_DISABLE;
  cfg.intr_type = GPIO_INTR_DISABLE;

  status |= gpio_config(&cfg);

  return status;
}

GpioInput::GpioInput(const gpio_num_t pin, const bool activeLow) {
  _init(pin, activeLow);
}

GpioInput::GpioInput(const gpio_num_t pin) {
  _init(pin, false);
}

GpioInput::GpioInput(void) {}

esp_err_t GpioInput::init(const gpio_num_t pin, const bool activeLow) {
  return _init(pin, activeLow);
}

esp_err_t GpioInput::init(const gpio_num_t pin) {
  return _init(pin, false);
}

int GpioInput::read(void) {
  return _active_low ? !gpio_get_level(_pin) : gpio_get_level(_pin);
}

esp_err_t GpioInput::enablePullup(void) {
  return gpio_set_pull_mode(_pin, GPIO_PULLUP_ONLY);
}

esp_err_t GpioInput::disablePullup(void) {
  return gpio_set_pull_mode(_pin, GPIO_FLOATING);
}

esp_err_t GpioInput::enablePulldown(void) {
  return gpio_set_pull_mode(_pin, GPIO_PULLDOWN_ONLY);
}

esp_err_t GpioInput::disablePulldown(void) {
  return gpio_set_pull_mode(_pin, GPIO_FLOATING);
}

esp_err_t GpioInput::enablePullupPulldown(void) {
  return gpio_set_pull_mode(_pin, GPIO_PULLUP_PULLDOWN);
}

esp_err_t GpioInput::disablePullupPulldown(void) {
  return gpio_set_pull_mode(_pin, GPIO_FLOATING);
}

esp_err_t GpioInput::enableInterrupt(gpio_int_type_t int_type) {
  esp_err_t status{ESP_OK};

  // Invert triggers if active low is enabled
  if (_active_low) {
    switch (int_type) {
      case GPIO_INTR_POSEDGE:
        int_type = GPIO_INTR_NEGEDGE;
        break;
      case GPIO_INTR_NEGEDGE:
        int_type = GPIO_INTR_POSEDGE;
        break;
      case GPIO_INTR_LOW_LEVEL:
        int_type = GPIO_INTR_HIGH_LEVEL;
        break;
      case GPIO_INTR_HIGH_LEVEL:
        int_type = GPIO_INTR_LOW_LEVEL;
        break;
      default:
        break;
    }
  }

  if (!_interrupt_service_installed) {
    status = gpio_install_isr_service(0);
    if (ESP_OK == status) {
      _interrupt_service_installed = true;
    }
  }

  if (ESP_OK == status) {
    status = gpio_set_intr_type(_pin, int_type);
  }

  if (ESP_OK == status) {
    status = gpio_isr_handler_add(_pin, gpio_isr_callback, (void*)_pin);
  }
  return status;
}

esp_err_t GpioInput::setEventHandler(esp_event_handler_t Gpio_e_h) {
  esp_err_t status{ESP_OK};

  status = esp_event_handler_instance_register(INPUT_EVENTS, _pin, Gpio_e_h, 0,
                                               nullptr);

  if (ESP_OK == status) {
    _event_handler_set = true;
  }
  return status;
}