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
	char temp[] = "Temperature: 30";
	char hum[] = "Humidity: 30";
	Screen_One(temp, hum);
	if(read_input() == 0){
		printf("worked");
	}
	Shutdown_Display();
	return 0;
}
