#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>      /* open() */
#include <unistd.h>     /* close() */
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/gpio.h>

//#include "c_func.h"

static int fd, rv;
static struct gpiohandle_request req;
static struct gpiohandle_data data;

void input_setup(void){

        /* Open the GPIO device and check for error */
        fd=open("/dev/gpiochip0",O_RDWR);
        if (fd == -1){
                // If file descriptor is -1, print the error and exit program
                printf("An error has occured: %s", strerror(errno));
                exit(1);
        }

        // Set up GPIO line
        memset(&req, 0, sizeof(struct gpiohandle_request));
        req.flags = GPIOHANDLE_REQUEST_INPUT;
        req.lines = 1;
        req.lineoffsets[0] = 5; // set to gpio5
        req.default_values[0] = 0;
        strcpy(req.consumer_label, "ECE471");
        rv = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);
        // Error checking for ioctl line
        if (rv == -1) {
                perror("Line error: ");
                exit(1);
        }
}

int read_input(void){
        // Run ioctl when called
        memset(&data, 0, sizeof(data));
        rv = ioctl(req.fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);

        // Error checking to make sure input was read in correctly
        if (rv == -1) {
                perror("GPIO value read error: ");
                exit(1);
        }

	// GPIO read result in data.values[0]
        int result = data.values[0];
	return !(result);
}
