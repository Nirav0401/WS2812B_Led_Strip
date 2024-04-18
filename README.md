# Neo Pixel LED Strip - WS2812B with RMT Driver

RMT peripheral is mainly designed for infrared remote applications, but it can also support other generic protocols. [WS2812](http://www.world-semi.com/Certifications/WS2812B.html) is a digital RGB LED which integrates a driver circuit and a single control wire. The protocol data format defined in WS2812B is compatible to that in RMT peripheral. This example will illustrate how to drive an WS2812B LED strip based on the RMT driver.

## How to Use Example

### Hardware Required

* A development board with ESP32 SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for Power supply and programming
* A WS2812B LED strip

Connection :

```
Input -> 5V
Output -> GPIO18 for Digital Input pin

```

### Configure the Project

Open the project configuration menu (`idf.py menuconfig`). 

* Set the GPIO number used for transmitting the IR signal under `RMT TX GPIO` option.
* Set the number of LEDs in a strip under `Number of LEDS in a strip` option.
* Here I have used RMT_TX_GPIO=18 and STRIP_LED_NUMBER=11.


### Build and Flash

Run `idf.py -p PORT flash monitor` to build, flash and monitor the project.

(To exit the serial monitor, type ``Ctrl-]``.)

## Example Output

````bash
Connect the Digital input pin of WS2812B LED strip to the GPIO pin which you set in menuconfig.

Run the example, you will see a red green blue and white colours in output.

Functions :

- void set_led_delay(uint16_t hue, uint16_t s, uint16_t v); -> function gives you delayed output of led colors.
- void clear_led() -> you can clear all the leds.

````

