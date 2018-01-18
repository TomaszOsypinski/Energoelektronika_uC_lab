/*
 * main.c
 *
 *  Created on: 2018 Jan 11 09:25:40
 *  Author: Tomasz Osypinski
 */

#include <DAVE.h>

/* Switch on pedantic checking */
/*
#if defined ( __GNUC__ )
#pragma GCC diagnostic warning "-pedantic"
#endif
*/
#define ONESEC (1000000UL)
#define GET_TIMESTAMP (DWT->CYCCNT)
#define CALC_DELT(t0, t1, delta) do{(t0 > t1) ? (delta = (t0 - t1)) : (delta = (t1 - t0));}while(0)
#define CALC_TIME_US(delta) ((float)delta * 0.006944444f)

void Tick_EverySec(void *args);
/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
volatile float a,b,c;
volatile double x,y,z;
volatile float procTimeFloat;
volatile float procTimeDoubleFloat;
int main(void)
{
    DAVE_STATUS_t status;
    register uint32_t t0;
    register uint32_t t1;
    register uint32_t delta;

    status = DAVE_Init(); /* Initialization of DAVE APPs  */

    if(status != DAVE_STATUS_SUCCESS)
    {
        /* Placeholder for error handler code. The while loop below can be
         * replaced with an user error handler. */
        XMC_DEBUG("DAVE APPs initialization failed\n");

        while(1U)
        {

        }
    }

    /* Create Software Timer with one second time interval in order to generate
     * software timer callback event at every second
     */
    uint32_t TimerId, TimerStatus;
    TimerId =
    SYSTIMER_CreateTimer(ONESEC, SYSTIMER_MODE_PERIODIC, Tick_EverySec, NULL);

    if(TimerId != 0U)

    {
        /* Timer is created successfully */
        /* Start/Run Software Timer */
        TimerStatus = SYSTIMER_StartTimer(TimerId);
        if(TimerStatus == SYSTIMER_STATUS_SUCCESS)
        {
            /* Timer is running */
        }
        else
        {
            /* Error during software timer start operation */
        }
    }
    else
    {
        /* Timer ID Can not be zero */
    }

    t0 = GET_TIMESTAMP;
    a = 0.5f;
    b = 2.0F;
    c = a * b;
    t1 = GET_TIMESTAMP;
    CALC_DELT(t0, t1, delta);
    procTimeFloat = CALC_TIME_US(delta);

    t0 = GET_TIMESTAMP;
    x = 2.0;
    y = 0.5;
    z = x * y;
    t1 = GET_TIMESTAMP;
    CALC_DELT(t0, t1, delta);
    procTimeDoubleFloat = CALC_TIME_US(delta);

    /* Placeholder for user application code. The while loop below can be replaced with user application code. */
    while(1U)
    {

    }
}

volatile uint32_t tick;
void Tick_EverySec(void * args)
{
    /* Parameter is not used, suppress unused argument warning */
    (void)args;
    tick++;
}

/* Switch off pedantic checking */
/*
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
*/
