// This file will hold code to run the ADA1893 sensor

// Datasheet used is below
// https://cdn-shop.adafruit.com/datasheets/1893_datasheet.pdf
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/ioctl.h>

#include <linux/i2c-dev.h>

// Global variables (used separate array for pressure, readings were getting mixed up)
static int fd_ada, result;
static char i2c_device[]="/dev/i2c-1";
static unsigned char buffer[17] = {0};
static unsigned char data_in[6] = {0};
static unsigned char data_pres[6] = {0};

// This function sets up the ADA1893 and prepares it for I2C transmission
void ada1893_setup(int alt_pres){
        // Open i2c device
        fd_ada = open("/dev/i2c-1", O_RDWR);
        // Error check to make sure file is open
        if(fd_ada < 0){
                perror("fd error: ");
                exit(1);
        }

        /* Set slave address */
        result=ioctl(fd_ada, I2C_SLAVE, 0x60);
        // Error check by ensuring result isn't negative
        if(result < 0){
                perror("Slave address error: ");
                exit(1);
        }
        //printf("Slave address bytes written: %d\n", result);

	if(alt_pres == 0){
		// Control register setup with altmeter mode
		buffer[0] = 0x26;
		buffer[1] = 0xB9; // Set altimeter mode
		result = write(fd_ada, buffer, 2);
        	if(result < 0){
                	perror("Control register setup error: ");
                	exit(1);
       		}
		//printf("Control register setup, bytes written: %d\n",result);
	}else if(alt_pres == 1){
                // Control register setup with barometer/pressure mode
                buffer[0] = 0x26;
                buffer[1] = 0x39; // Set barometer mode
                result = write(fd_ada, buffer, 2);
                if(result < 0){
                        perror("Control register setup error: ");
                        exit(1);
                }
                //printf("Control register setup, bytes written: %d\n",result);
	}

	// Enable data flags
	buffer[0] = 0x13;
	buffer[1] = 0x07;
	result = write(fd_ada, buffer, 2);
        if(result < 0){
                perror("Data flag setup error: ");
                exit(1);
        }
	//printf("Data flag bytes written: %d\n",result);

	// Give device time to configure before reading
	usleep(1000000);
}

// This function reads and processes the temperature in celsius
int read_temp(){
	// Read in values and store in data_in array
	result = read(fd_ada, data_in, 6);
	// Error check reading
	if(result != 6){
                perror("Data read error: ");
                exit(1);
	}

	// Obtain temperature reading in celsius (12 bit, ignore last 4 bits of data_in[5])
	int tempC = ((data_in[4] * 256) + (data_in[5] & 0xF0)) / 256;
	return tempC;
}

// This function reads and processes the altitude in meters (use 0 for setup function argument)
int read_alt(){
        // Read in values and store in data_in array
        result = read(fd_ada, data_in, 6);
        // Error check reading
        if(result != 6){
                perror("Data read error: ");
                exit(1);
        }

	// Obtain altitude reading in meters (20 bit, ignore last 4 bits of data_in[3])
	int altM = ((data_in[1] * 65536) + (data_in[2] * 256) + (data_in[3] & 0xF0)) / 256;
        return altM;
}

// This function reads and processes the pressure in kPa (use 1 for setup function argument)
int read_pres(){
        // Read in values and store in data_in array
        result = read(fd_ada, data_pres, 6);
        // Error check reading
        if(result != 6){
                perror("Data read error: ");
                exit(1);
        }

	// Obtain pressure reading in kPa (20 bit, ignore last 4 bits of data_in[3])
	int pres_kPa = 4 * ((data_pres[1] * 65536) + (data_pres[2] * 256) + (data_pres[3] & 0xF0)) / 256000;
	return pres_kPa;
}

// This function closes the file descriptor and ends transmission with the sensor
void shutdown_ada(){
	close(fd_ada);
}
