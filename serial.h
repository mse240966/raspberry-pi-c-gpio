#ifndef SERIAL_H_INCLUDED
#define SERIAL_H_INCLUDED

#include <termios.h>

static const char GPIO_SERIAL_DEFAULT_DEVICE[] = "/dev/ttyAMA0";

typedef struct serial
{
    const char *device;

    int fileDescriptor;
    struct termios configuration;

    char *data;

    ssize_t bytesWritten;

    ssize_t bytesToRead;
    ssize_t bytesRead;

} GPIO_SERIAL_PARAMETERS;

int gpioSerialOpenDevice(GPIO_SERIAL_PARAMETERS *serialParameters);
int gpioSerialCloseDevice(const GPIO_SERIAL_PARAMETERS serialParameters);
int gpioSerialWriteDevice(GPIO_SERIAL_PARAMETERS *serialParameters);
int gpioSerialReadDevice(GPIO_SERIAL_PARAMETERS *serialParameters);

#endif // SERIAL_H_INCLUDED
