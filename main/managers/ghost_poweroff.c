#include "ghost_poweroff.h"
#include "driver/gpio.h"
#include "esp_sleep.h"
#include "freertos/task.h"

void ghost_poweroff(void) {
    // Configure GPIO 15 as output (power control pin on T-Display S3)
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << 15,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);

    // Turn off display / power rail
    gpio_set_level(15, 0);

    // Small delay to ensure shutdown happens
    vTaskDelay(pdMS_TO_TICKS(120));

    // Enter deep sleep (board will fully turn off)
    esp_deep_sleep_start();
}
