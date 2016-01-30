#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <stdbool.h>

static const char GPIO_EXPORT[] = "/export";
static const char GPIO_UNEXPORT[] = "/unexport";
static const char GPIO_DIRECTION[] = "/direction";
static const char GPIO_VALUE[] = "/value";
static const char GPIO_PIN_DIR[] = "/gpio%d";

static const int GPIO_INPUT = 0;
static const int GPIO_OUTPUT = 1;

static const int GPIO_LOW = 0;
static const int GPIO_HIGH = 1;

int gpioExport(const int pin);
int gpioExportAndDirection(const int pin, const int direction);
int gpioDirection(const int pin, const int direction);
int gpioWrite(const int pin, const int value);
int gpioRead(const int pin, int *value);
int gpioUnexport(const int pin);
void gpioTestMode(char *gpioSysClass);
void gpioVerbose(const bool verbose);
bool gpioIsValidPin(const int pin);

static const int GPIO_PIN_02 = 2;
static const int GPIO_PIN_03 = 3;
static const int GPIO_PIN_04 = 4;
static const int GPIO_PIN_05 = 5;
static const int GPIO_PIN_06 = 6;
static const int GPIO_PIN_07 = 7;
static const int GPIO_PIN_08 = 8;
static const int GPIO_PIN_09 = 9;
static const int GPIO_PIN_10 = 10;
static const int GPIO_PIN_11 = 11;
static const int GPIO_PIN_12 = 12;
static const int GPIO_PIN_13 = 13;
static const int GPIO_PIN_14 = 14;
static const int GPIO_PIN_15 = 15;
static const int GPIO_PIN_16 = 16;
static const int GPIO_PIN_17 = 17;
static const int GPIO_PIN_18 = 18;
static const int GPIO_PIN_19 = 19;
static const int GPIO_PIN_20 = 20;
static const int GPIO_PIN_21 = 21;
static const int GPIO_PIN_22 = 22;
static const int GPIO_PIN_23 = 23;
static const int GPIO_PIN_24 = 24;
static const int GPIO_PIN_25 = 25;
static const int GPIO_PIN_26 = 26;
static const int GPIO_PIN_27 = 27;

#endif // GPIO_H_INCLUDED
