#include "main.h"

Main App;

led_strip_handle_t Main::configure_led(void)
{
    // LED strip general initialization, according to your led board design
    led_strip_config_t strip_config;
    strip_config.strip_gpio_num =
        LED_STRIP_BLINK_GPIO;  // The GPIO that connected to the
                               // LED strip's data line
    strip_config.max_leds = 1; // The number of LEDs in the strip,
    strip_config.led_pixel_format =
        LED_PIXEL_FORMAT_GRB;                  // Pixel format of your LED strip
    strip_config.led_model = LED_MODEL_WS2812; // LED strip model
    strip_config.flags.invert_out = false;     // whether to invert the output signal

    // LED strip backend configuration: SPI
    led_strip_spi_config_t spi_config;
    spi_config.clk_src = SPI_CLK_SRC_DEFAULT; // different clock source can lead
                                              // to different power consumption
    spi_config.flags.with_dma = true;         // Using DMA can improve performance and
                                              // help drive more LEDs
    spi_config.spi_bus = SPI2_HOST;           // SPI bus ID

    // LED Strip object handle
    led_strip_handle_t led_strip;
    ESP_ERROR_CHECK(
        led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
    ESP_LOGI(TAG, "Created LED strip object with SPI backend");
    return led_strip;
}

void Main::run(void)
{
    if (!input_1.read())
    {
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 0, 5, 0));
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        output_1.setLevel(1);
        output_2.setLevel(1);
        output_3.setLevel(1);
    }else{
        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 5, 0, 0));
        ESP_ERROR_CHECK(led_strip_refresh(led_strip));
        output_1.setLevel(0);
        output_2.setLevel(0);
        output_3.setLevel(0);
    }
}

void Main::setup(void) {
    input_1.enableInterrupt(GPIO_INTR_POSEDGE);
    input_1.setEventHandler(&button_event_handler);
}

extern "C" void app_main(void)
{

    ESP_LOGI(TAG, " starting firmware ");

    App.led_strip = App.configure_led();
    ESP_ERROR_CHECK(led_strip_set_pixel(App.led_strip, 0, 0, 0, 5));
    ESP_ERROR_CHECK(led_strip_refresh(App.led_strip));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

    esp_event_loop_create_default();

    App.setup();

    while (true)
    {
        App.run();
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }    
}

void Main::button_event_handler(void* handler_args,
                                esp_event_base_t base,
                                int32_t id,
                                void* event_data) {

    std::cout << "Button triggered interrupt with ID: " << id << '\n';
}
