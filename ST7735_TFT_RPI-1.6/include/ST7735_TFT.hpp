/*!
	@file     ST7735_TFT.hpp
	@author   Gavin Lyons
	@brief    Library header file for ST7735_TFT_RPI library.
				Contains driver methods for ST7735_TFT display

	@note  See URL for full details.https://github.com/gavinlyonsrepo/ST7735_TFT_RPI
		
*/

#pragma once

// Section Libraries 
#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "ST7735_TFT_graphics.hpp" // Custom


// Section:  Defines

// ST7735 registers + Commands

// ST7735 general purpose
#define ST7735_NOP     0x00 /**< Non operation */
#define ST7735_SWRESET 0x01 /**< Soft Reset */
#define ST7735_RDDID   0x04 /**< Read Display ID*/
#define ST7735_RDDST   0x09 /**< Read Display Status*/

// ST7735 Modes
#define ST7735_SLPIN   0x10 /**< Sleep ON */
#define ST7735_SLPOUT  0x11 /**< Sleep OFF */
#define ST7735_PTLON   0x12 /**< Partial mode */
#define ST7735_NORON   0x13 /**< Normal Display */
#define ST7735_INVOFF  0x20 /**< Display invert off */
#define ST7735_INVON   0x21 /**< Display Invert on */
#define ST7735_DISPOFF 0x28 /**< Display off */
#define ST7735_DISPON  0x29 /**< Display on */
#define ST7735_TFT_Idle_modeON 0x39 /**< Idle Mode ON */
#define ST7735_TFT_Idle_modeOF  0x38 /**< Idle Mode OFF */

// ST7735 Addressing 
#define ST7735_CASET   0x2A /**< Column address set */
#define ST7735_RASET   0x2B /**<  Page address set */
#define ST7735_RAMWR   0x2C /**< Memory write */
#define ST7735_RAMRD   0x2E /**< Memory read */
#define ST7735_PTLAR   0x30 /**< Partial Area */
#define ST7735_VSCRDEF 0x33 /**< Vertical scroll def */
#define ST7735_COLMOD  0x3A /**< Interface Pixel Format */
#define ST7735_MADCTL  0x36 /**< Memory Access Control */
#define ST7735_VSCRSADD 0x37 /**< Vertical Access Control */

// Frame Rate Control
#define ST7735_FRMCTR1 0xB1 /**< Normal */
#define ST7735_FRMCTR2 0xB2 /**< idle */
#define ST7735_FRMCTR3 0xB3 /**< Partial */

#define ST7735_INVCTR  0xB4 /**< Display Inversion control */
#define ST7735_DISSET5 0xB6 /**< Display Function set */

// ST7735 Power_Control
#define ST7735_PWCTR1  0xC0 /**< Power_Control VRH: Set the GVDD voltage */
#define ST7735_PWCTR2  0xC1 /**< Power_Control BT: set VGH/ VGL voltage */
#define ST7735_PWCTR3  0xC2 /**< Power_Control APA: adjust op amp & DCA: boost Voltage */
#define ST7735_PWCTR4  0xC3 /**< Power_Control APB: adjust op amp & DCB: boost Voltage */
#define ST7735_PWCTR5  0xC4 /**< Power_Control APC: adjust op amp & DCC: boost Voltage */
#define ST7735_PWCTR6  0xFC /**< Power_Control In partial mode + Idle */

#define ST7735_VMCTR1  0xC5 /**< VCOM_Control 1 */

#define ST7735_RDID1   0xDA /**< read ID1 */
#define ST7735_RDID2   0xDB /**< read ID2  */
#define ST7735_RDID3   0xDC /**< read ID3  */
#define ST7735_RDID4   0xDD /**< read ID4  */

// ST7735 color control
#define ST7735_GMCTRP1 0xE0 /**< Positive Gamma Correction Setting */
#define ST7735_GMCTRN1 0xE1 /**< Negative Gamma Correction Setting */

// Memory Access Data Control  Register 
#define ST7735_MADCTL_MY 0x80 /**< Row Address Order */
#define ST7735_MADCTL_MX 0x40 /**< Column Address Order */
#define ST7735_MADCTL_MV 0x20 /**< Row/Column Order (MV) */
#define ST7735_MADCTL_ML 0x10 /**< Vertical Refresh Order */
#define ST7735_MADCTL_RGB 0x00 /**< RGB order */
#define ST7735_MADCTL_BGR 0x08 /**< BGR order */
#define ST7735_MADCTL_MH 0x04  /**< Horizontal Refresh Order */

// Color definitions 16-Bit Color Values R5G6B5
#define   ST7735_BLACK   0x0000
#define   ST7735_BLUE    0x001F
#define   ST7735_RED     0xF800
#define   ST7735_GREEN   0x07E0
#define   ST7735_CYAN    0x07FF
#define   ST7735_MAGENTA 0xF81F
#define   ST7735_YELLOW  0xFFE0
#define   ST7735_WHITE   0xFFFF
#define   ST7735_TAN     0xED01
#define   ST7735_GREY    0x9CD1
#define   ST7735_BROWN   0x6201
#define   ST7735_DGREEN  0x01c0
#define   ST7735_ORANGE  0xFC00


// GPIO
#define TFT_DC_SetHigh  bcm2835_gpio_write(_TFT_DC, HIGH)
#define TFT_DC_SetLow  bcm2835_gpio_write(_TFT_DC, LOW)
#define TFT_RST_SetHigh  bcm2835_gpio_write(_TFT_RST, HIGH)
#define TFT_RST_SetLow  bcm2835_gpio_write(_TFT_RST, LOW)
#define TFT_CS_SetHigh bcm2835_gpio_write(_TFT_CS, HIGH) 
#define TFT_CS_SetLow bcm2835_gpio_write(_TFT_CS, LOW)
#define TFT_SCLK_SetHigh bcm2835_gpio_write(_TFT_SCLK, HIGH)
#define TFT_SCLK_SetLow  bcm2835_gpio_write(_TFT_SCLK, LOW)
#define TFT_SDATA_SetHigh bcm2835_gpio_write(_TFT_SDATA, HIGH)
#define TFT_SDATA_SetLow  bcm2835_gpio_write(_TFT_SDATA,LOW)

#define TFT_DC_SetDigitalOutput bcm2835_gpio_fsel(_TFT_DC, BCM2835_GPIO_FSEL_OUTP)
#define TFT_RST_SetDigitalOutput bcm2835_gpio_fsel(_TFT_RST, BCM2835_GPIO_FSEL_OUTP)
#define TFT_SCLK_SetDigitalOutput bcm2835_gpio_fsel(_TFT_SCLK, BCM2835_GPIO_FSEL_OUTP) 
#define TFT_SDATA_SetDigitalOutput bcm2835_gpio_fsel(_TFT_SDATA, BCM2835_GPIO_FSEL_OUTP)
#define TFT_CS_SetDigitalOutput bcm2835_gpio_fsel(_TFT_CS, BCM2835_GPIO_FSEL_OUTP)

// Delays
#define TFT_MILLISEC_DELAY bcm2835_delay
#define TFT_MICROSEC_DELAY bcm2835_delayMicroseconds
#define TFT_HIGHFREQ_DELAY 0 // Optional Software SPI delay uS


/*! 
	@brief Class to control ST7735 TFT basic functionality.
*/
class ST7735_TFT : public ST7735_TFT_graphics
{

public:

	ST7735_TFT();
	~ST7735_TFT(){};
	
	//  Enums

	/*! TFT display modes */
	enum TFT_modes_e : uint8_t 
	{
		TFT_Normal_mode = 0,  /**< In this mode, the display is able to show maximum 262*/
		TFT_Partial_mode,  /**< In this mode part of the display is used with maximum 262*/
		TFT_Idle_mode, /**< In this mode, part of the display is used but with 8 colors.*/
		TFT_Sleep_mode, /**<  In this mode, the DC: DC converter, internal oscillator and panel driver circuit are stopped. Only the MCU interface and
						memory works with VDDI power supply. Contents of the memory are safe.*/
		TFT_Invert_mode, /**< Invert display colors */
		TFT_Display_on_mode, 
		TFT_Display_off_mode /**< In this mode, both VDD and VDDI are removed.*/
	};

	/*! TFT rotate modes in degrees*/
	enum  TFT_rotate_e : uint8_t
	{
		TFT_Degrees_0 = 0, /**< No rotation 0 degrees*/
		TFT_Degrees_90,    /**< Rotation 90 degrees*/
		TFT_Degrees_180,   /**< Rotation 180 degrees*/
		TFT_Degrees_270   /**< Rotation 270 degrees*/
	}; 

	/*! TFT type type of PCB */
	enum TFT_PCBtype_e: uint8_t 
	{
		TFT_ST7735R_Red = 0, /**<  ST7735R Red Tab  */
		TFT_ST7735R_Green,   /**<  ST7735R Green Tab */
		TFT_ST7735S_Black,   /**<  ST7735S Black Tab */
		TFT_ST7735B,         /**<  ST7735B controller */
	}; 

	TFT_modes_e TFT_mode;       /**< Enum to hold display mode */
	TFT_PCBtype_e TFT_PCBtype;  /**< Enum to hold TFT type  */
	
	void TFTSetupGPIO(int8_t, int8_t, int8_t, int8_t, int8_t);
	void TFTInitScreenSize(uint8_t xOffset, uint8_t yOffset, uint16_t w, uint16_t h);
	int8_t TFTInitPCBType(TFT_PCBtype_e pcbType, uint32_t hertz = 0, uint8_t SPICE_Pin = 0 );
	void TFTPowerDown(void);
	
	void TFTsetRotation(TFT_rotate_e r);
	void TFTchangeInvertMode(bool invertModeOn);
	void TFTchangeMode(TFT_modes_e m);
	void TFTsetScrollDefinition(uint8_t th, uint8_t tb, bool sd);
	void TFTVerticalScroll(uint8_t vsp);
	
private:

	void TFTResetPIN(void);
	void TFTSPIInitialize(void);
	void TFTST7735BInitialize(void);
	void TFTGreenTabInitialize(void);
	void TFTBlackTabInitialize(void);
	void TFTRedTabInitialize(void);
	void Rcmd1(void);
	void Rcmd2red(void);
	void Rcmd3(void);
	void Bcmd(void);
	void Rcmd2green(void);
	
	uint8_t  _rotation = 0; /**< variable to hold Rotation mode 0-3*/
	uint32_t _hertz;        /**< Spi freq in Hertz , MAX 125 Mhz MIN 30Khz */
	uint8_t  _SPICEX_pin;  /**< value = X , which SPI_CE pin to use */

}; //end of ST7735_TFT  class

// ********************** EOF *********************
