#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"
#include "sh1106.h"

sh1106 lcd;

int main(){
    lcd.bus_init();
    lcd.screen_init();
    lcd.clear_screen();
}