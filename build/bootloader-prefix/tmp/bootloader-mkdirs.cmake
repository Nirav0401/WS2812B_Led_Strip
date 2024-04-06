# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Espressif/v4.4.4/esp-idf/components/bootloader/subproject"
  "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader"
  "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader-prefix"
  "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader-prefix/tmp"
  "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader-prefix/src/bootloader-stamp"
  "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader-prefix/src"
  "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "E:/Local/Documents/Embedded_C/ESP_Projects/led_strip/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
