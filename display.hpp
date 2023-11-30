#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_graphics.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_Print.hpp"

int8_t Setup(void);
void Test_Text(void);
void Shutdown_Display(void);
void Screen_One(char* temp, char* pressure, char* temp_min, char* temp_max, char* pres_min, char* pres_max);
void Screen_Two(char* alt, char* gas, char* alt_min, char* alt_max, char* gas_min, char* gas_max);
void Screen_Three(char* temp, char* pres, char* alt, char* gas);
