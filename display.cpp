// Compile with: g++ -o display display.cpp display_func.cpp input.c -lbcm2835 -lrt -lST7735_TFT_RPI
// Run using: sudo ./display

#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "display.hpp"
extern "C" {
//	#include "c_func.h"  // Include the C header
	#include "input.c"
}


int main(void) {
	input_setup();
	if(!Setup())return -1;

	// Create buffers and variables for readings
	char pres[30], temp[30], gas[30], alt[30];
	int temp_read, pres_read, gas_read, alt_read, temp_max, pres_max, gas_max, alt_max = 0;
	// Infinite loop to allow for continuous use
	while(1){
		// Use functions to read temperatures
		temp_read = 20; // Replace with function when written, additional comments
		std::sprintf(temp, "Temperature: %d F", temp_read); // Fill in buffers with text to be displayed

	        pres_read = 42;
	        std::sprintf(pres, "Pressure: %d Pa", pres_read);

		gas_read = 52;
                std::sprintf(gas, "Gas: %d cf", gas_read);

		alt_read = 62;
                std::sprintf(alt, "Altitude: %d ft", alt_read);

		// Collect maximum readings
		if (temp_read > temp_max) temp_max = temp_read;
		if (pres_read > pres_max) pres_max = pres_read;
		if (alt_read > alt_max) alt_max = alt_read;
		if (gas_read > gas_max) gas_max = gas_read;

		// Change screen if button is pressed, cycles through
		if (read_input() == 1){
			while(1){
				Screen_Two(alt, gas);
				delay(1000);
				if (read_input() == 1){
					while(1){
						Screen_Three(temp, pres, alt, gas);
                                		delay(1000);
                                		if (read_input() == 1) break;
					}
					if (read_input() == 1) break;
				}
			}
		}
		Screen_One(temp, pres);
		delay(1000);
	}
	Shutdown_Display();
	return 0;
}
