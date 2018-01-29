/*
 * main.c
 *
 *  Created on: 2018 Jan 25 10:55:53
 *  Author: Tomasz Osypinski
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code. It is responsible for
 * invoking the APP initialization dispatcher routine - DAVE_Init() and hosting the place-holder for user application
 * code.
 */
volatile float g_duty = 50.0f;

int main(void)
{
    DAVE_STATUS_t status;

    status = DAVE_Init(); /* Initialization of DAVE APPs  */

    if(status != DAVE_STATUS_SUCCESS)
    {
        /* Placeholder for error handler code. The while loop below can be replaced with an user error handler. */
        XMC_DEBUG("DAVE APPs initialization failed\n");

        while(1U)
        {

        }
    }

    /* Placeholder for user application code. The while loop below can be replaced with user application code. */
    while(1U)
    {
        if(g_duty > 100.0f)
        {
            g_duty = 100.0f;
        }
        else if(g_duty < 0.0f)
        {
            g_duty = 0.0f;
        }
        PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_0,
                                       XMC_CCU8_SLICE_COMPARE_CHANNEL_1,
                                       ((uint32_t)g_duty * PWM_CCU8_DUTY_SCALE));
    }
}
