#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
//#include "c_func.h"

// I2C device address for the SGP30 sensor
#define SGP30_I2C_ADDR 0x58

// SGP30 commands
#define SGP30_INIT_CMD 0x2003
#define SGP30_MEASURE_CMD 0x2008

static int file_sgp;
static char *filename = "/dev/i2c-1";

// This code seemed to work only half the time, so returning -1 instead of exiting. This allows device to still run

//Initalization function
int sgp30Init(){
        // Open I2C bus
    if ((file_sgp = open(filename, O_RDWR)) < 0) {
        perror("Failed to open the i2c bus");
        return -1;
    }

    // Set I2C device address
    if (ioctl(file_sgp, I2C_SLAVE, SGP30_I2C_ADDR) < 0) {
        perror("Failed to acquire bus access and/or talk to slave");
        return -1;
    }

    // Initialize SGP30
    unsigned char init_cmd[2] = {(SGP30_INIT_CMD>>8) & 0XFF, 0x03};
    if (write(file_sgp, init_cmd, sizeof(init_cmd)) != sizeof(init_cmd)) {
        perror("Failed to send SGP30 init command");
        return -1;
    }
    sleep(1); // Wait for initialization
    return 1;
}

int sgp30Measure(){
//	struct SGP30Values values;

	//Measure and read CO2 and TVOC values
    unsigned char measure_cmd[2] = {(SGP30_MEASURE_CMD >> 8) & 0xFF, SGP30_MEASURE_CMD & 0xFF};
    if (write(file_sgp, measure_cmd, sizeof(measure_cmd)) != sizeof(measure_cmd)) {
        perror("Failed to send SGP30 measure command");
        return 0;
    }

    sleep(1);

    // Read 6 bytes of data (CO2 MSB, CO2 LSB, CRC, TVOC MSB, TVOC LSB, CRC)
    unsigned char data[6];
    if (read(file_sgp, data, sizeof(data)) != sizeof(data)) {
        perror("Failed to read SGP30 measurement data");
        return 0;
    }

    // Calculate CO2
    int values = (data[0] << 8) | data[1];

    // TVOC readings didn't seem to work, so ignoring
    //values = (data[3] << 8) | data[4];
    return values;
}
