#include "driver/gpio.h"
#include "esp_sleep.h"
#include "freertos/task.h"

void ghost_poweroff(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = 1ULL << 15,
        .mode = GPIO_MODE_OUTPUT,
        .pull_down_en = 0,
        .pull_up_en = 0,
        .intr_type = GPIO_INTR_DISABLE,
    };

    gpio_config(&io_conf);
    gpio_set_level(15, 0);  // Turn off display power

    vTaskDelay(pdMS_TO_TICKS(100));

    esp_deep_sleep_start();
}
