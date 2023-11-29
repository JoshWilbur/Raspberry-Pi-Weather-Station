
// This will contain interfacing for the gas sensor

//Git test PC #2

//Git test Pi

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "sgp30.h"
// I2C device address for the SGP30 sensor
#define SGP30_I2C_ADDR 0x58

// SGP30 commands
#define SGP30_INIT_CMD 0x2003
#define SGP30_MEASURE_CMD 0x2008

//Initalization function
void sgp30Init(int file){
    // Set I2C device address
    if (ioctl(file, I2C_SLAVE, SGP30_I2C_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        exit(1);
    }

    // Initialize SGP30
    unsigned char init_cmd[2] = {(SGP30_INIT_CMD>>8) & 0XFF, 0x03};
    if (write(file, init_cmd, sizeof(init_cmd)) != sizeof(init_cmd)) {
        perror("Failed to send SGP30 init command");
        exit(1);
    }
    sleep(1); // Wait for initialization
}

struct SGP30Values sgp30Measure(int file){
	struct SGP30Values values;

//Measure and read CO2 and TVOC values
    unsigned char measure_cmd[2] = {(SGP30_MEASURE_CMD >> 8) & 0xFF, SGP30_MEASURE_CMD & 0xFF};
    if (write(file, measure_cmd, sizeof(measure_cmd)) != sizeof(measure_cmd)) {
        perror("Failed to send SGP30 measure command");
        exit(1);
    }

    sleep(1);

    // Read 6 bytes of data (CO2 MSB, CO2 LSB, CRC, TVOC MSB, TVOC LSB, CRC)
    unsigned char data[6];
    if (read(file, data, sizeof(data)) != sizeof(data)) {
        perror("Failed to read SGP30 measurement data");
        exit(1);
    }

    // Calculate CO2 and TVOC values
    values.co2 = (data[0] << 8) | data[1];
    values.tvoc = (data[3] << 8) | data[4];



	return values;
}


int main() {
	int file;
	char *filename = "/dev/i2c-1";

	// Open I2C bus
    if ((file = open(filename, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        exit(1);
    }
	sgp30Init(file);
	while(1){
		struct SGP30Values values;
		values = sgp30Measure(file);

		// Print values in the terminal
		printf("CO2 Concentration: %u ppm\n", values.co2);
		printf("TVOC Concentration: %u ppb\n", values.tvoc);

	}
	    // Close I2C bus
	    close(file);
	    return 0;
}
