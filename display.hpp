#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_graphics.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_Print.hpp"

int8_t Setup(void);
void Test_Text(void);
void Shutdown_Display(void);
void Screen_One(char* temp, char* pressure);
void Screen_Two(char* alt, char* gas);
void Screen_Three(char* temp, char* pres, char* alt, char* gas);
