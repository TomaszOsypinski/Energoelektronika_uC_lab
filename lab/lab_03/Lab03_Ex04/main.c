/*
 * main.c
 *
 *  Created on: 2018 Jan 25 10:55:53
 *  Author: Tomasz Osypinski
 */




#include <DAVE.h>                 //Declarations from DAVE Code Generation (includes SFR declaration)

#define TRIP                P0_7
#define BUTTON_1            P15_13
#define READ_BUTTON1        (XMC_GPIO_GetInput(BUTTON_1))

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
        /* Half bridge */
        PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_0,
                                       XMC_CCU8_SLICE_COMPARE_CHANNEL_1,
                                       ((uint32_t)(g_duty / 2.0f) * PWM_CCU8_DUTY_SCALE));

        PWM_CCU8_SetDutyCycleSymmetric(&PWM_CCU8_0,
                                       XMC_CCU8_SLICE_COMPARE_CHANNEL_2,
                                       ((uint32_t)(100.0f -(g_duty/2.0f)) * PWM_CCU8_DUTY_SCALE));

       if(READ_BUTTON1)
       {
           XMC_GPIO_SetOutputHigh(TRIP);
       }
       else
       {
           XMC_GPIO_SetOutputLow(TRIP);
       }
    }
}

/* ISR */
volatile uint32_t cntControlLoopIsr;
volatile uint16_t idc;
void ControlLoopIsr(void)
{
    cntControlLoopIsr++;
    XMC_GPIO_ToggleOutput(XMC_GPIO_PORT3, 12);
    idc = ((uint16_t)vadc_group_0.group_ptr->RES[0]) >> 1U;
}
