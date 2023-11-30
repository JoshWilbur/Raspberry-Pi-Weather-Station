// Compile with: g++ -o display display.cpp display_func.cpp input.c ADA1893.c -lbcm2835 -lrt -lST7735_TFT_RPI
// Run using: sudo ./display

#include <bcm2835.h>
#include <iostream>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "display.hpp"
extern "C" {
	#include "input.c"
	#include "ADA1893.c"
}


int main(void) {
	input_setup();
	if(!Setup())return -1;
	ada1893_setup(0);

	// Create buffers and variables for readings
	char pres[30], temp[30], gas[30], alt[30], p_min[30], t_min[30], g_min[30], a_min[30], p_max[30], t_max[30], g_max[30], a_max[30];
	int temp_read, pres_read, gas_read, alt_read, temp_max, pres_max, gas_max, alt_max = 0;
	int temp_min = 999;
	int pres_min = 999;
	int gas_min = 999;
	int alt_min = 999;

	// Infinite loop to allow for continuous use
	while(1){
		// Run the functions defined in the other programs
		ada1893_setup(0);
		temp_read = read_temp();
		std::sprintf(temp, "Temperature: %d C", temp_read); // Fill in buffers with text to be displayed

                alt_read = read_alt();
                std::sprintf(alt, "Altitude: %d M", alt_read);

		ada1893_setup(1);
	        pres_read = read_pres();
	        std::sprintf(pres, "Pressure: %d kPa", pres_read);

		gas_read = 52;
                std::sprintf(gas, "Gas: %d ppm", gas_read);

		// Collect maximum readings
		if (temp_read > temp_max) temp_max = temp_read;
		if (pres_read > pres_max) pres_max = pres_read;
		if (alt_read > alt_max) alt_max = alt_read;
		if (gas_read > gas_max) gas_max = gas_read;

                // Collect minimum readings
                if (temp_read < temp_min) temp_min = temp_read;
                if (pres_read < pres_min) pres_min = pres_read;
                if (alt_read < alt_min) alt_min = alt_read;
                if (gas_read < gas_min) gas_min = gas_read;

	 	std::sprintf(t_min, "Min Temp.: %d C", temp_min);
		std::sprintf(t_max, "Max Temp.: %d C", temp_max);
                std::sprintf(p_min, "Min Pres.: %d kPa", pres_min);
                std::sprintf(p_max, "Max Pres.: %d kPa", pres_max);

                std::sprintf(a_min, "Min Alt.: %d M", alt_min);
                std::sprintf(a_max, "Max Alt.: %d M", alt_max);
                std::sprintf(g_min, "Min Gas: %d ppm", gas_min);
                std::sprintf(g_max, "Max Gas: %d ppm", gas_max);

		// Change screen if button is pressed, cycles through
		if (read_input() == 1){
			while(1){
				Screen_Two(alt, gas, a_min, a_max, g_min, g_max);
				delay(1000);
				if (read_input() == 1) break;
			}
		}
		Screen_One(temp, pres, t_min, t_max, p_min, p_max);
		delay(1000);
	}
	Shutdown_Display();
	return 0;
}
