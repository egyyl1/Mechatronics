#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

/* Only needed in Windows program to maintain compatibility with Arduino version of C/C++ */
#define bool BOOL
#define true 1
#define false 0
const bool FWDS = true;
const bool BWDS = false;

const long ticksPerSec = 1000; // ms on PC
// on Arduino it is 1E6 for micros (for s/w) or 1.6E7 for 62.5 ns ticks (for h/w)

void moveOneStep();
void computeNewSpeed();
long computeStepsToGo();
void goToPosition(long newPosition);
long millis(void);

/* Note: we are using global variables ONLY to preserve compatibility with the Arduino program structure.
   They should not normally be used in C or C++ programs as they make for a poor software design. */
/* Global variables relating to stepper motor position counting etc. */
long stepsToGo;             /* Number of steps left to make in present movement */
long targetPosition;        /* Intended destination of motor for given movement */
volatile long currentPosition = 0;   /* Position in steps of motor relative to startup position */
float maxSpeed;            /* Maximum speed in present movement (not nec. max permitted) */
bool direction;             /* Direction of present movement: FWDS or BWDS */

/* Global variables used in simplistic and Leib Ramp algorithms */
volatile float p;   /* Step interval in clock ticks or microseconds */
float ps;       /* Maximum step periods */
float deltaP;      /* You'll be able to get rid of this later */

/* Global variable used for noting previous time of a step in timed loop and for calculating speed and accel */
long prevStepTime=0;
long millisAtStart;
float prevSpeed=0.0;

/* Define permissible parameters for motor */
// For testing on PC only, not for use in Arduino program: try movements in order of 50-100 steps
float accelSteps=20; /* leave this as a variable as we may over-write it */
const float minSpeed = 1.0;  // in steps/s
const float maxPermissSpeed = 20.0;   // in steps/s
const float maxAccel = 10.0;     // in steps/s^2

int main()
{
    unsigned long currentMillis = millis();
    prevStepTime = 0;
    long positionToMoveTo;
    while(true)
    {
        printf("Enter position to move to in profile (or 999 to terminate)\n");
        scanf("%ld", &positionToMoveTo);
        if (positionToMoveTo==999) break;
        printf("        Time (s),  Speed (steps/s), Accel (steps/s^2),  Posit'n (steps), Step time (ticks)\n");

        goToPosition(positionToMoveTo);

        /* -------------------------------------------------------------- */
        /* Start of pre-computation code - only executed once per profile */
        
        float maxInterval = ((float)ticksPerSec) / minSpeed;
        ps = ((float)ticksPerSec) / maxPermissSpeed;
        deltaP = (maxInterval - ps) / accelSteps;
        stepsToGo = computeStepsToGo();
        maxSpeed = maxPermissSpeed;
        if (2 * accelSteps > stepsToGo)
        {
            accelSteps = (long)(stepsToGo / 2);
        }

        p = maxInterval;
        
        ps = ((float)ticksPerSec) / maxSpeed;
        /* End of pre-computation code                                    */
        /* -------------------------------------------------------------- */
        millisAtStart = millis(); /* Needed only to tabulate speed vs. time */

        /* Timed loop for stepping */
        while(stepsToGo > 0)
        {
            currentMillis = millis();
            if (currentMillis - prevStepTime >= p)
            {
               moveOneStep();
               prevStepTime = currentMillis;
               computeNewSpeed();
            }
        }
    }
    return 0;
}

long millis(void)
/* Only needed for compatibility with Arduino program because millis() is not a native Windows API function */
{
    return GetTickCount();
}

void moveOneStep()
/* Move a single step.  If this were running on the Arduino we would holding pulse high for delayMicroSeconds */
{
  if (p != 0) /* p=0 is code for "don't make steps" */
  {
    // Print to screen instead of making a step
    if (direction == FWDS)
    {
      currentPosition++;
    }
    else
    {
      currentPosition--;
    }
    
    /* Instead of actually making step, print out parameters for current step */
    float speed = (float)(ticksPerSec)/p;
    float accel = (float)(ticksPerSec)*(speed-prevSpeed)/p;
    printf("%16.3f, %16.3f,  %16.3f, %16ld, %16.3f\n", 0.001*(millis()-millisAtStart), speed, accel, currentPosition, p);
    prevSpeed = speed;
  }
}

/* Calcuate new value of step interval p based on constants defined in timed loop */
void computeNewSpeed()
{
  stepsToGo = computeStepsToGo();

  /* Start of on-the-fly step calculation code, executed once per step */
  if (stepsToGo == 0)
  {
    p = 0; // Not actually a zero step interval, used to switch stepping off
    return;
  }
  else if (stepsToGo >= accelSteps && (long)p > (long)ps) // Changed to make ramps even length
  /* Speeding up */
  {
    p -= deltaP;
  }
  else if (stepsToGo <= accelSteps)
  /* Slowing down */
  {
    p += deltaP;
  }
  /* else p is unchanged: running at constant speed */

  /* End of on-the-fly step calculation code */
}

/* Work out how far the stepper motor still needs to move */
long computeStepsToGo()
{
  if (direction == FWDS)
  {
    return targetPosition - currentPosition;
  }
  else
  {
    return currentPosition - targetPosition;
  }
}

/* Set the target position and determine direction of intended movement */
void goToPosition(long newPosition)
{
  targetPosition = newPosition;
  if (targetPosition - currentPosition > 0)
  {
    direction = FWDS;
  }
  else
  {
    direction = BWDS;
  }
}