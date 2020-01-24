/*
 Change the Intensity of LED using PWM on Raspberry Pi
 http://www.electronicwings.com
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>

#include "iconfig.h"
#include "igardener.h"
#include "ipump.h"
#include "itimer.h"

const int PWM0_pin = 1; /* GPIO 1 as per WiringPi, GPIO18 as per BCM */
const int PWM1_pin = 24;

int main(void)
{
  int intensity;

  if (wiringPiSetup() == -1)
  {
    exit(1);
  }

  pinMode(PWM0_pin, PWM_OUTPUT); /* set PWM pin as output */
  pinMode(PWM1_pin, PWM_OUTPUT);

  while (1)
  {
    for (intensity = 0; intensity < 1024; intensity++)
    {
      pwmWrite(PWM0_pin, intensity); /* provide PWM value for duty cycle */
      delay(1);
    }

    delay(10000);

    for (intensity = 1023; intensity >= 0; intensity--)
    {
      pwmWrite(PWM0_pin, intensity);
      delay(1);
    }

    delay(1);
#if 1
    for (intensity = 0; intensity < 1024; intensity++)
    {
      pwmWrite(PWM1_pin, intensity); /* provide PWM value for duty cycle */
      delay(1);
    }

    delay(10000);

    for (intensity = 1023; intensity >= 0; intensity--)
    {
      pwmWrite(PWM1_pin, intensity);
      delay(1);
    }

    delay(1);
#endif
  }
}
