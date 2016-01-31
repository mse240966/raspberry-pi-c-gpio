#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#include "serial.h"

/*
 * Open serial device
 */
int gpioSerialOpenDevice(GPIO_SERIAL_PARAMETERS *serialParameters)
{
    serialParameters->fileDescriptor = open(serialParameters->device, O_RDWR | O_NOCTTY | O_NDELAY);
    if (serialParameters->fileDescriptor == -1)
    {
        printf("Error opening serial device %s\n", serialParameters->device);
        return EXIT_FAILURE;
    }

    if (tcgetattr(serialParameters->fileDescriptor, &serialParameters->configuration) < 0)
    {
        printf("Error reading configuration of serial device %s\n", serialParameters->device);
        return EXIT_FAILURE;
    }

    // Default settings
    serialParameters->configuration.c_iflag = 0;
    serialParameters->configuration.c_oflag = 0;
    serialParameters->configuration.c_lflag = 0;
    serialParameters->configuration.c_cflag = 0;
    serialParameters->configuration.c_cc[VMIN] = 0;
    serialParameters->configuration.c_cc[VTIME] = 0;
    serialParameters->configuration.c_cflag = B115200 | CS8 | CREAD;

    // Should ever want to change default setting, I can expose a function to do this
    if (tcsetattr(serialParameters->fileDescriptor, TCSANOW, &serialParameters->configuration) < 0)
    {
        printf("Error writing configuration on serial device %s\n", serialParameters->device);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Close serial device
 */
int gpioSerialCloseDevice(const GPIO_SERIAL_PARAMETERS serialParameters)
{
    return close(serialParameters.fileDescriptor);
}

/*
 * Write to serial device
 */
int gpioSerialWriteDevice(GPIO_SERIAL_PARAMETERS *serialParameters)
{
    serialParameters->bytesWritten = write(serialParameters->fileDescriptor,
                                           serialParameters->data,
                                           strlen(serialParameters->data));

    if (serialParameters->bytesWritten < 0)
    {
        printf("Error writing to serial device %s\n", serialParameters->device);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
 * Read from serial device
 */
int gpioSerialReadDevice(GPIO_SERIAL_PARAMETERS *serialParameters)
{
    char buffer[serialParameters->bytesToRead + 1];

    serialParameters->bytesRead = read(serialParameters->fileDescriptor,
                                       buffer,
                                       sizeof(buffer));

    serialParameters->data = malloc((sizeof(char) * serialParameters->bytesRead));
    strcpy(serialParameters->data, buffer);
    serialParameters->data[serialParameters->bytesRead] = '\0';

    return EXIT_SUCCESS;
}
