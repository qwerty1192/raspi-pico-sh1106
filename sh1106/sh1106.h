#ifndef _sh1106
#define _sh1106

#define SH1106_WRITE_ADDR   0x3C
#define SH1106_READ_ADDR    0x3D

//Command Table
#define LOW_COLUMN_ADDR         0x00
#define HIGH_COLUMN_ADDR        0x10
#define DISPLAY_START_LINE      0x40
#define SET_CONTRAST_REG_ADDR   0x81
#define SET_SEGMENT_REMAP       0xA1 //127 to 0
#define SET_CTRL_AS_RAM         0xA4 //The controller follows the RAM data
#define SET_ALLPIXEL_ON         0xA5 //The controller ignores RAM data and turns on the entire display
#define SET_NORMAL_DISPLAY      0xA6
#define SET_REVERSE_DISPLAY     0xA7
#define SET_MULTIPLEX_RATIO     0xA8
#define DISPLAY_OFF             0xAE
#define DISPLAY_ON              0xAF
#define SET_PAGE_ADDR           0xB0 //0 to 7
#define SET_DISPLAY_OFFSET      0xD3
#define SET_DISPLAY_CLOCK       0xD5
#define SET_PRECHARGE_PERIOD    0xD9
#define SET_COM_PADS_CONFIG     0xDA
#define SET_VCOM_DESELECT_LEVEL 0xDB

//Screen size
#define MAX_PAGE_COUNT  8
#define SCREEN_WIDTH    132
#define SCREEN_HEIGHT   64

class sh1106{
public:
void bus_init(i2c_inst_t * 	i2c, uint sda, uint scl);
void oled_init(void);

void fill_screen(bool f_data);
void clear_screen(void);
};

#endif