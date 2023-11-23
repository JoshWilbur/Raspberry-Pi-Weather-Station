#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <thread>
#include <chrono>

#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_graphics.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT.hpp"
#include "ST7735_TFT_RPI-1.6/include/ST7735_TFT_Print.hpp"

// This function will handle function declarations for the "display.hpp" header file

// Global struct myTFT
ST7735_TFT myTFT;


// Static declaration of functions
int8_t Setup(void);
void Test_Text(void);
void Screen_One(char* temp, char* pressure);
void Screen_Two(char* alt, char* gas);
void Screen_Three(char* temp, char* pres, char* alt, char* gas);
void Shutdown_Display(void);

// This function will create the layout for displaying temperature and humidity
void Screen_One(char* temp, char* pressure){
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTsetRotation(myTFT.TFT_Degrees_270); // Rotate screen so its in landscape mode
	myTFT.TFTfillRect(0, 62, 160, 4, ST7735_GREEN); // Green horizontal line
	myTFT.TFTFontNum(myTFT.TFTFont_Tiny);
	myTFT.TFTdrawText(4, 20, temp, ST7735_WHITE, ST7735_BLACK, 2); // Display temperature
        myTFT.TFTdrawText(4, 90, pressure, ST7735_WHITE, ST7735_BLACK, 2); // Display humidity
}

// This function will create the layout for displaying altitude and gas
void Screen_Two(char* alt, char* gas){
        myTFT.TFTfillScreen(ST7735_BLACK);
        myTFT.TFTsetRotation(myTFT.TFT_Degrees_270); // Rotate screen so its in landscape mode
        myTFT.TFTfillRect(0, 62, 160, 4, ST7735_CYAN); // Green horizontal line
        myTFT.TFTFontNum(myTFT.TFTFont_Tiny);
        myTFT.TFTdrawText(4, 20, alt, ST7735_WHITE, ST7735_BLACK, 2); // Display altitude
        myTFT.TFTdrawText(4, 90, gas, ST7735_WHITE, ST7735_BLACK, 2); // Display gas reading
}

// This function will display the maximum values of each reading
void Screen_Three(char* temp, char* pres, char* alt, char* gas){
        myTFT.TFTfillScreen(ST7735_BLACK);
        myTFT.TFTsetRotation(myTFT.TFT_Degrees_270); // Rotate screen so its in landscape mode
	myTFT.TFTfillRect(0, 20, 160, 4, ST7735_BLUE); // Green horizontal line
	myTFT.TFTfillRect(0, 50, 160, 4, ST7735_ORANGE); // Green horizontal line
	myTFT.TFTfillRect(0, 80, 160, 4, ST7735_YELLOW); // Green horizontal line
	myTFT.TFTfillRect(0, 105, 160, 4, ST7735_MAGENTA); // Green horizontal line
        myTFT.TFTFontNum(myTFT.TFTFont_Tiny);
	myTFT.TFTdrawText(20, 0, "Maximum Readings", ST7735_WHITE, ST7735_BLACK, 2); // Display max temperature
        myTFT.TFTdrawText(4, 25, temp, ST7735_WHITE, ST7735_BLACK, 2); // Display max temperature
        myTFT.TFTdrawText(4, 55, pres, ST7735_WHITE, ST7735_BLACK, 2); // Display max pressure
        myTFT.TFTdrawText(4, 85, alt, ST7735_WHITE, ST7735_BLACK, 2); // Display max altitude
        myTFT.TFTdrawText(4, 110, gas, ST7735_WHITE, ST7735_BLACK, 2); // Display max gas reading
}

// Setup function from TFT library (
int8_t Setup(void)
{
	std::cout << "TFT Start" << std::endl;
	if(!bcm2835_init())
	{
		std::cout << "Error : Problem with init bcm2835 library" << std::endl;
		return -1;
	}

// GPIO/SPI TYPE
	int8_t RST_TFT  = 25;
	int8_t DC_TFT   = 24;
	int8_t SCLK_TFT = -1;   // 5, change to any GPIO no for sw spi, -1 hw spi
	int8_t SDIN_TFT = -1;   // 6, change to any GPIO no for sw spi, -1 hw spi
	int8_t CS_TFT   = -1;  // 8, change to any GPIO no for sw spi, -1 hw spi
	myTFT.TFTSetupGPIO(RST_TFT, DC_TFT, CS_TFT, SCLK_TFT, SDIN_TFT);


// Screen Setup
	uint8_t OFFSET_COL = 0;  // 2, These offsets can be adjusted for any issues->
	uint8_t OFFSET_ROW = 0; // 3, with manufacture tolerance/defects
	uint16_t TFT_WIDTH = 128; // Screen width
	uint16_t TFT_HEIGHT = 160; // Screen height
	myTFT.TFTInitScreenSize(OFFSET_COL, OFFSET_ROW , TFT_WIDTH , TFT_HEIGHT);

// PCB_TYPE + SPI baud rate + SPI_CE_PIN
	uint32_t SCLK_FREQ =  8000000 ; // HW Spi only , freq in Hertz , MAX 125 Mhz MIN 30Khz
	uint8_t SPI_CE_PIN = 0; // HW Spi only which HW SPI chip enable pin to use,  0 or 1
	if(!myTFT.TFTInitPCBType(myTFT.TFT_ST7735R_Red, SCLK_FREQ, SPI_CE_PIN))return -1;
	return 0;
}

void Test_Text(void) {
	char teststr1[] = "testing"; // String to hold what is printed
	myTFT.TFTfillScreen(ST7735_BLACK);
	myTFT.TFTFontNum(myTFT.TFTFont_Default);
        myTFT.TFTfillScreen(ST7735_BLACK);
        myTFT.TFTsetRotation(myTFT.TFT_Degrees_90); // Rotate screen so its in landscape mode
	myTFT.TFTdrawText(15, 30, teststr1, ST7735_WHITE, ST7735_BLACK, 1);
	std::this_thread::sleep_for(std::chrono::seconds(3)); // Display for three seconds before ending function
}

void Shutdown_Display(void)
{
	myTFT.TFTPowerDown(); // Power down device
	bcm2835_close(); // Close the bcm2835 library
	std::cout << "TFT End" << std::endl;
}
