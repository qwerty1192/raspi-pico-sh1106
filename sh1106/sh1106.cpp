#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "sh1106.h"

#define SDA_PIN 8
#define SCL_PIN 9
#define I2C_PORT i2c0

int main(){
    i2c_init(I2C_PORT, 100 * 1000);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);
    bi_decl(bi_2pins_with_func(SDA_PIN, SCL_PIN, GPIO_FUNC_I2C));

    uint8_t buf[8] = {0x00,0xAF};
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);

    buf[1] = 0xA5;
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);
    sleep_ms(1500);
    buf[1] = 0xA4;
    i2c_write_blocking(I2C_PORT, SH1106_WRITE_ADDR, buf, 2, 0);
}

void sh1106::init(void){

}