#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "sh1106.h"

#define SDA_PIN 4
#define SCL_PIN 5
#define I2C_PORT i2c0
sh1106 lcd;

int main(){
    lcd.bus_init(I2C_PORT,SDA_PIN,SCL_PIN);
    lcd.oled_init();
    lcd.clear_screen();
/*
    uint8_t buf[8] = {0x00,0xAF};
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);

    buf[1] = 0xA5;
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);
    sleep_ms(1500);
    buf[1] = 0xA4;
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);
    sleep_ms(1500);
    uint8_t a = 0xA5;
    lcd.send_cmd(&a,1);
    */
}

void sh1106::bus_init(i2c_inst_t * i2c, uint sda, uint scl){
    i2c_init(i2c, 100 * 1000);
    gpio_set_function(sda, GPIO_FUNC_I2C);
    gpio_set_function(scl, GPIO_FUNC_I2C);
    gpio_pull_up(sda);
    gpio_pull_up(scl);
    bi_decl(bi_2pins_with_func(sda, scl, GPIO_FUNC_I2C));
}

void sh1106::oled_init(void){
    uint8_t buf[2]{0x00, DISPLAY_OFF};  //Co = 0 , D/C = 0
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);

    buf[1] = DISPLAY_ON;
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);
}

void sh1106::fill_screen(bool f_data){
    uint8_t data[133] = {f_data};
    data[0] = 0x40;
    for(int page=0;page<MAX_PAGE_COUNT;page++){
        uint8_t buf[4]{0x00,SET_PAGE_ADDR+page,LOW_COLUMN_ADDR,HIGH_COLUMN_ADDR};
        i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 4, 0);
        i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, data, 133, 0);
    }
}

void sh1106::clear_screen(void){
    fill_screen(0);
}