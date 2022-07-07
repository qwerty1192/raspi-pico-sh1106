cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(sh1106 C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.3.0")
    message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.3.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_compile_options(-Wall
        -Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        -Wno-maybe-uninitialized
        )

add_executable(sh1106
        example.cpp
        sh1106.cpp
        )

target_link_libraries(sh1106 pico_stdlib hardware_i2c)

pico_add_extra_outputs(sh1106)

pico_enable_stdio_usb(sh1106 1)
pico_enable_stdio_uart(sh1106 0)
