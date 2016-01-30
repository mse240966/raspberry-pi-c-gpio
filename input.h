#ifndef INPUT_H_INCLUDED
#define INPUT_H_INCLUDED

#include <stdbool.h>
#include <pthread.h>

typedef struct inp
{
    // Constant parameters
    const int gpioPin;
    const int sleepDelay;

    // Variable parameters
    int inputValue;

    // Set to true to gracefully terminate the thread
    bool terminate;

    // Thread Id (Internal variable, not to be set)
    pthread_t threadId;

    // Input value changed function pointer
    void (*inputValueChanged)(int);

} GPIO_INPUT_PARAMETERS;

int gpioInputStart(GPIO_INPUT_PARAMETERS *inputParameters);
int gpioInputStop(GPIO_INPUT_PARAMETERS *inputParameters);
void *gpioInputPollPin(void *inputParameters);

#endif // INPUT_H_INCLUDED
