#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "pwm.h"
#include "gpio.h"

static void pulseCycle(GPIO_PWM_PARAMETERS *pwmParameters);
static void pulseGpioPin(const int gpioPin, const int value, const int pulseLength);
static void calculateDutyCycle(GPIO_PWM_PARAMETERS *pwmParameters);

/*
 * Start the pulse width modulation thread
 */
int gpioPwmStart(GPIO_PWM_PARAMETERS *pwmParameters)
{
    return pthread_create(&pwmParameters->threadId, NULL, &gpioPwmCyclePin, (void*)pwmParameters);
}

/*
 * Stop the pulse width modulation thread and wait for thread to terminate
 */
int gpioPwmStop(GPIO_PWM_PARAMETERS *pwmParameters)
{
    pwmParameters->terminate = true;
    return pthread_join(pwmParameters->threadId, NULL);
}

/*
 * Pulse Width Modulation thread function. Pass a pointer to a GPIO_PWM_PARAMETERS struct.
 * Passing as a pointer means the duty cycle can be changed whilst the thread is executing.
 * Its software pulse width modulation so not very accurate!
 */
void *gpioPwmCyclePin(void *parameters)
{
    GPIO_PWM_PARAMETERS *pwmParameters = (GPIO_PWM_PARAMETERS *)parameters;

    // Validate GPIO pin
    assert(gpioIsValidPin(pwmParameters->gpioPin) == true);

    while(pwmParameters->terminate == false)
    {
        // Parameters can be changed outside of this thread, so need to re-calulate every iteration
        calculateDutyCycle(pwmParameters);

        pulseCycle(pwmParameters);
    }

    pthread_exit(NULL);
}

/*
 * Similiar to above, but pulses for a defined length of time
 */
void gpioPwmPulsePin(GPIO_PWM_PARAMETERS *pwmParameters)
{
    calculateDutyCycle(pwmParameters);

    for (int pulse = 0; pulse < pwmParameters->lengthOfPulse; pulse++)
    {
        pulseCycle(pwmParameters);
    }
}

/*
 * Do a pulse cycle
 */
static void pulseCycle(GPIO_PWM_PARAMETERS *pwmParameters)
{
    // Set pin high and sleep for high cycle
    if (pwmParameters->microSecondsHigh > 0)
    {
        pulseGpioPin(pwmParameters->gpioPin, GPIO_HIGH, pwmParameters->microSecondsHigh);
    }

    // Set pin low and sleep for low cycle
    if (pwmParameters->microSecondsLow > 0)
    {
        pulseGpioPin(pwmParameters->gpioPin, GPIO_LOW, pwmParameters->microSecondsLow);
    }
}

/*
 * Pulse a gpio pin
 */
static void pulseGpioPin(const int gpioPin, const int value, const int pulseLength)
{
    // Validate GPIO pin
    assert(gpioIsValidPin(gpioPin) == true);

    int returnStatus = gpioWrite(gpioPin, value);
    assert(returnStatus == EXIT_SUCCESS);
    usleep(pulseLength);
}

/*
 * Calculate duty cycle in micro seconds
 */
static void calculateDutyCycle(GPIO_PWM_PARAMETERS *pwmParameters)
{
    pwmParameters->microSecondsTotal = (int)(GPIO_PWM_UNIT_MICRO_SECOND / pwmParameters->cyclesPerSecond);
    pwmParameters->microSecondsHigh = pwmParameters->microSecondsTotal * (float)(pwmParameters->dutyCycle / GPIO_PWM_HUNDRED_PERCENT);
    pwmParameters->microSecondsLow = pwmParameters->microSecondsTotal - pwmParameters->microSecondsHigh;
}
