#!/bin/bash
cd /home/jlw/Raspberry-Pi-Weather-Station

# Compile display.cpp program
if g++ -o display display.cpp display_func.cpp input.c ADA1893.c SGP30.c -lbcm2835 -lrt -lST7735_TFT_RPI; then
	# Run display.cpp
	echo "Compilation worked"
	sudo ./display
else
	echo "Compilation failed. Check for errors."
fi
