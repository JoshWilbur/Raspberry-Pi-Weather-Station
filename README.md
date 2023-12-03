# Raspberry-Pi-Weather-Station
Authors: Joshua Wilbur, Amir Seidakhmetov, Henry Willard

This repo will hold the code for a Raspberry Pi 2B weather station. An ADA1893 and SGP30 were used to collect data on temperature, pressure, altitude and gas levels. User input is collected through a push button. The ST7735_TFT_RPI-1.6 library by Gavin Lyons is used to interface with a 1.8" TFT LCD display over SPI. This library is used for initial setup and basic interfacing of the display.

A bash script was made to compile and run the code. Running ./weather_station_script.sh inside the directory runs the program. An image of the weather station is in the repo, the SGP30 is not present.
