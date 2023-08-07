set(srcs "src/cppgpio_input.cpp"
    "src/cppgpio_output.cpp")

idf_component_register(SRCS "${srcs}"
    INCLUDE_DIRS "include"
    REQUIRES "driver"
    REQUIRES "esp_event")