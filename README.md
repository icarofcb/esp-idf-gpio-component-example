| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# Example: esp-idf-gpio-component-example

This test code shows how to configure GPIO and how to use it with interruption using GPIO as a component on a CPP project for esp-idf, it also has a SPI driver for WS2812 RGB led.

## GPIO functions:

| GPIO                         | Direction | Configuration                                          |
| ---------------------------- | --------- | ------------------------------------------------------ |
| output_1                     | output    |                                                        |
| output_2                     | output    |                                                        |
| output_3                     | output    |                                                        |
| LED_STRIP_BLINK_GPIO         | output    | SPI driver for WS2812                                  |
| input_1                      | input     | pulled up, interrupt from rising edge                  |

## Test:
The example uses GPIO0 as input where normally we have a button attached to the port for BOOT porpuses, but in this example the button is going to be used for triggering a interruption and also control the configure outputs.

## How to use example

Before project configuration and build, be sure to set the correct chip target using `idf.py set-target <chip_name>`

### Build and Flash

Build the project and flash it to the board, then run the monitor tool to view the serial output:

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

### Hardware Required

* A development board with any Espressif SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for Power supply and programming
* Some jumper wires to connect GPIOs.

## Example folder contents

The project **esp-idf-gpio-component-example** contains one source file in C++ language [main.cpp](main/main.cpp). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── components
│   ├── cppgpio
│   │   ├── CMakeLists.txt
│   │   ├── idf_component.yml
│   │   ├── include
│   │   │   └── cppgpio.h
│   │   └── src
│   │       ├── cppgpio_input.cpp
│   │       └── cppgpio_output.cpp
│   └── espressif_led_strip_2.4.1
│       ├── CMakeLists.txt
│       ├── idf_component.yml
│       ├── README.md
│       ├── include
│       │   ├── led_strip.h
│       │   ├── led_strip_rmt.h
│       │   ├── led_strip_spi.h
│       │   └── led_strip_types.h
│       ├── include
│       │   └──  led_strip_interface.h
│       └── src
│           ├── led_strip_api.c
│           ├── led_strip_rmt_dev.c
│           ├── led_strip_rmt_encoder.c
│           ├── led_strip_rmt_encoder.h
│           └── led_strip_spi_dev.cpp
├── main
│   ├── CMakeLists.txt
│   ├── main.h
│   └── main.cpp
└── README.md                  This is the file you are currently reading
```
