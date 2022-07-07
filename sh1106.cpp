#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "sh1106.h"

#define SDA_PIN 4
#define SCL_PIN 5
#define I2C_PORT i2c0

void sh1106::bus_init(){
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));
}

void sh1106::screen_init(void){
    uint8_t buf[2]{0x00, DISPLAY_OFF};  //Co = 0 , D/C = 0
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);

    buf[1] = DISPLAY_ON;
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);
}

void sh1106::_fillscreen(bool s_data){
    uint8_t buf[4]{0x00,SET_PAGE_ADDR,LOW_COLUMN_ADDR,HIGH_COLUMN_ADDR};
    uint8_t data[133] = {s_data};
    data[0] = 0x40;
    for(int page=0;page<MAX_PAGE_COUNT;page++){
        buf[1] = SET_PAGE_ADDR+page;
        i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 4, 0);
        i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, data, 133, 0);
    }
}

void sh1106::fill_screen(void){
    _fillscreen(1);
}

void sh1106::clear_screen(void){
    _fillscreen(0);
}