/* RMT example -- RGB LED Strip

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt.h"
#include "led_strip.h"

static const char *TAG = "example";

#define RMT_TX_CHANNEL RMT_CHANNEL_0

#define EXAMPLE_CHASE_SPEED_MS (50)


uint32_t red = 0;
uint32_t green = 0;
uint32_t blue = 0;

// Define the LED strip configuration and driver globally
led_strip_config_t strip_config;
led_strip_t *strip;

/**
 * @brief Simple helper function, converting HSV color space to RGB color space
 *
 * Wiki: https://en.wikipedia.org/wiki/HSL_and_HSV
 *
 */
void led_strip_hsv2rgb(uint32_t h, uint32_t s, uint32_t v, uint32_t *r, uint32_t *g, uint32_t *b)
{
    h %= 360; // h -> [0,360]
    uint32_t rgb_max = v * 2.55f;
    uint32_t rgb_min = rgb_max * (100 - s) / 100.0f;

    uint32_t i = h / 60;   //120 for green  -> 2   // 240 for blue  -> 4
    uint32_t diff = h % 60;  //             -> 0   //              -> 0

    // RGB adjustment amount by hue
    uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;   // 0   // 0

    switch (i) {
    case 0:
        *r = rgb_max;
        *g = rgb_min + rgb_adj;
        *b = rgb_min;
        break;
    case 1:
        *r = rgb_max - rgb_adj;
        *g = rgb_max;
        *b = rgb_min;
        break;
    case 2:
        *r = rgb_min;                // 0
        *g = rgb_max;                // 255
        *b = rgb_min + rgb_adj;     // 0
        break;
    case 3:
        *r = rgb_min;
        *g = rgb_max - rgb_adj;
        *b = rgb_max;
        break;
    case 4:
        *r = rgb_min + rgb_adj;    // 0
        *g = rgb_min;              // 0
        *b = rgb_max;              // 255
        break;
    default:
        *r = rgb_max;
        *g = rgb_min;
        *b = rgb_max - rgb_adj;
        break;
    }
}

// Initialize the LED strip driver and configuration
void initialize_led_strip() {
    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(CONFIG_EXAMPLE_RMT_TX_GPIO, RMT_TX_CHANNEL);
    // Set counter clock to 40MHz
    config.clk_div = 2;

    ESP_ERROR_CHECK(rmt_config(&config));
    ESP_ERROR_CHECK(rmt_driver_install(config.channel, 0, 0));

    // Install ws2812 driver
    led_strip_config_t strip_config = LED_STRIP_DEFAULT_CONFIG(CONFIG_EXAMPLE_STRIP_LED_NUMBER, (led_strip_dev_t)config.channel);
    strip = led_strip_new_rmt_ws2812(&strip_config);
    if (!strip) {
        ESP_LOGE(TAG, "install WS2812 driver failed");
    }

    // Clear LED strip (turn off all LEDs)
    ESP_ERROR_CHECK(strip->clear(strip, 100));
    // Show simple rainbow chasing pattern
    ESP_LOGI(TAG, "RGB LED Chase Start");
}

// Function to set LED strip to a specified color
void set_led(uint16_t hue, uint16_t s, uint16_t v)
{
    // Set LED strip to the specified color
    for (int i = 0; i < CONFIG_EXAMPLE_STRIP_LED_NUMBER; i++) {
        // Build RGB values
        led_strip_hsv2rgb(hue, s, v, &red, &green, &blue);
        // Write RGB values to strip driver
        ESP_ERROR_CHECK(strip->set_pixel(strip, i, red, green, blue));
    }
        // Refresh LED strip to apply the color changes
        ESP_ERROR_CHECK(strip->refresh(strip, 10));
        vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
}

// Function to set LED strip with delay to a specified color
void set_led_delay(uint16_t hue, uint16_t s, uint16_t v) {
    // Set LED strip to the specified color
    for (int i = 0; i < CONFIG_EXAMPLE_STRIP_LED_NUMBER; i++) {
        // Build RGB values
        led_strip_hsv2rgb(hue, s, v, &red, &green, &blue);
        // Write RGB values to strip driver
        ESP_ERROR_CHECK(strip->set_pixel(strip, i, red, green, blue));

        // Refresh LED strip to apply the color changes
        ESP_ERROR_CHECK(strip->refresh(strip, 10));
        vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
    }

    // Turn off each LED
    for (int i = 0; i < CONFIG_EXAMPLE_STRIP_LED_NUMBER; i++) {
        // Write black color to turn off the LED
        ESP_ERROR_CHECK(strip->set_pixel(strip, i, 0, 0, 0));
    }
        // Refresh LED strip to apply the color changes
        ESP_ERROR_CHECK(strip->refresh(strip, 0));  // Refresh immediately to turn off LEDs
        vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));  // Wait for the specified delay

}

void clear_led()
{
    // Turn off each LED
    for (int i = 0; i < CONFIG_EXAMPLE_STRIP_LED_NUMBER; i++) {
        // Write black color to turn off the LED
        ESP_ERROR_CHECK(strip->set_pixel(strip, i, 0, 0, 0));
    }
    // Refresh LED strip to apply the color changes
    ESP_ERROR_CHECK(strip->refresh(strip, 0));  // Refresh immediately to turn off LEDs
    vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));  // Wait for the specified delay

}


void app_main(void)
{
    initialize_led_strip();

    while (true) {

    // Example usage of set_color function
    set_led(0, 100, 100);  // Set LED strip to red color
    vTaskDelay(pdMS_TO_TICKS(5000));  // Wait for 5 seconds
    set_led(120, 100, 100);  // Set LED strip to green color
    vTaskDelay(pdMS_TO_TICKS(5000));  // Wait for 5 seconds
    // set_led(240, 100, 100);  // Set LED strip to blue color
    // vTaskDelay(pdMS_TO_TICKS(5000));  // Wait for 5 seconds
    // set_led(0, 0, 100);  // Set LED strip to blue color
    // vTaskDelay(pdMS_TO_TICKS(5000));  // Wait for 5 seconds
    // clear_led();
    // vTaskDelay(pdMS_TO_TICKS(5000));  // Wait for 5 seconds
    // set_led_delay(0, 100, 100);
    // vTaskDelay(pdMS_TO_TICKS(5000));  // Wait for 5 seconds
        
    }
}
