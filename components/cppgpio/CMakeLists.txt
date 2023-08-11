set(srcs "src/gpio/cppgpio_input.cpp"
    "src/gpio/cppgpio_output.cpp")

idf_component_register(SRCS "${srcs}"
    INCLUDE_DIRS "include/gpio"
    REQUIRES "driver"
    REQUIRES "esp_event")