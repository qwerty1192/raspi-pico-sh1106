add_executable(sh1106
        sh1106.cpp
        )

target_link_libraries(sh1106 pico_stdlib hardware_i2c)

pico_add_extra_outputs(sh1106)

pico_enable_stdio_usb(sh1106 1)
pico_enable_stdio_uart(sh1106 0)