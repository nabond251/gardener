/**
 * @brief Gardener main application.
 */

#include "main.h"

#include "config.h"
#include "igardener.h"
#include "ipump.h"
#include "timer.h"

using namespace gardener;
using namespace std;

const int PWM0_pin = 1; /* GPIO 1 as per WiringPi, GPIO18 as per BCM */
const int PWM1_pin = 24;

/**
 * @brief   Gardener execution entry point.
 *
 * @param   [in] argc   CLI argument count.
 * @param   [in] argv   CLI argument vector.
 *
 * @returns 0 if executed successfully, else error code.
 */
int main(int argc, char *argv[])
{
    cout << argv[0]
         << "Version "
         << Gardener_VERSION_MAJOR
         << "."
         << Gardener_VERSION_MINOR
         << endl;

    Config *cfg = new Config(10, 1);
    Timer *tmr = new Timer();
    tmr->reload(100);
    tmr->isExpired();

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
