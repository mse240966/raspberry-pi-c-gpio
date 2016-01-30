#ifndef PWM_H_INCLUDED
#define PWM_H_INCLUDED

#include <stdbool.h>
#include <pthread.h>

typedef struct pwm
{
    // Constant parameters
    const int gpioPin;

    // Variable parameters
    int cyclesPerSecond;
    float dutyCycle;
    int lengthOfPulse;

    // Set to true to gracefully terminate the thread
    bool terminate;

    // Thread Id (Internal variable, not to be set)
    pthread_t threadId;

    // Duty cycle variables (Internal variable, not to be set)
    int microSecondsTotal;
    int microSecondsHigh;
    int microSecondsLow;

} GPIO_PWM_PARAMETERS;

static const int GPIO_PWM_UNIT_MICRO_SECOND = 1000000;
static const float GPIO_PWM_HUNDRED_PERCENT = 100.0f;

static const int GPIO_PWM_DUTY_CYCLE_HIGH = 100;
static const int GPIO_PWM_DUTY_CYCLE_LOW = 0;

int gpioPwmStart(GPIO_PWM_PARAMETERS *pwmParameters);
int gpioPwmStop(GPIO_PWM_PARAMETERS *pwmParameters);

void *gpioPwmCyclePin(void *pwmParameters);
void gpioPwmPulsePin(GPIO_PWM_PARAMETERS *pwmParameters);

#endif // PWM_H_INCLUDED
