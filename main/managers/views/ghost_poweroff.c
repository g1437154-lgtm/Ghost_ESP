#include "driver/gpio.h"
#include "esp_sleep.h"
#include "freertos/task.h"

// Simple power-off function for T-Display S3
void ghost_poweroff(void) {

    // Turn OFF backlight (GPIO 15 on T-Display S3)
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << 15,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);
    gpio_set_level(15, 0);

    // Small delay to let screen power down cleanly
    vTaskDelay(pdMS_TO_TICKS(150));

    // Deep sleep (device “OFF”)
    esp_deep_sleep_start();
}
