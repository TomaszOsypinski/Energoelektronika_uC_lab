/**
 *******************************************************************************
 * @file    main.c
 * @version 0.1.0
 * @date    Jan 11, 2018
 * @brief   Enter brief Description of this module.
 * @author  Tomasz Osypinski\n 
 *          e-mail: tomaszo@medcom.com.pl
 * @details Project name:\n
 *          Project number:\n
 *
 * Revision history:\n
 * \n
 * version:     0.1.0\n
 * date:        Jan 11, 2018\n
 * author:      Tomasz Osypinski\n
 * description: Working version\n
 *******************************************************************************
 */

/*
 *******************************************************************************
 * the includes
 *******************************************************************************
 */
#include <stdio.h>
#include <xmc_common.h>
#include <xmc_gpio.h>

/* Switch on pedantic checking */
#if defined ( __GNUC__ )
#pragma GCC diagnostic warning "-pedantic"
#endif

/*
 *******************************************************************************
 * #defines
 *******************************************************************************
 */
#define TICKS_PER_SECOND    (1000UL)
#define SYS_TICKS_1MS       (SystemCoreClock / TICKS_PER_SECOND)

#define LED_1               P5_9
#define LED_2               P5_8

#define LED1_SET            (XMC_GPIO_SetOutputHigh(LED_1))
#define LED1_CLR            (XMC_GPIO_SetOutputLow(LED_1))
#define LED1_TOGGEL         (XMC_GPIO_ToggleOutput(LED_1))

#define LED2_SET            (XMC_GPIO_SetOutputHigh(LED_2))
#define LED2_CLR            (XMC_GPIO_SetOutputLow(LED_2))
#define LED2_TOGGEL         (XMC_GPIO_ToggleOutput(LED_2))

#define BUTTON_1            P15_13
#define BUTTON_2            P15_12

#define READ_BUTTON1        (XMC_GPIO_GetInput(BUTTON_1))
#define READ_BUTTON2        (XMC_GPIO_GetInput(BUTTON_2))

/*
#define PRINT_TEXT printf("This is first line!\n");\
                   printf("This is second line!\n")
*/


/*
#define PRINT_TEXT {printf("This is first line!\n");\
                    printf("This is second line!\n");}
*/


#define PRINT_TEXT do{ printf("This is first line!\n");\
                       printf("This is second line!\n");} while(0)


/*
 *******************************************************************************
 * global variables
 *******************************************************************************
 */

/*
 *******************************************************************************
 * local variables
 *******************************************************************************
 */

/*
 *******************************************************************************
 * the function prototypes
 *******************************************************************************
 */

/*
 *******************************************************************************
 * the external functions
 *******************************************************************************
 */

/*
 *******************************************************************************
 * the functions
 *******************************************************************************
 */

int main(void)
{
    /* Configure GP Outputs */
    XMC_GPIO_CONFIG_t config;
    config.mode = XMC_GPIO_MODE_OUTPUT_PUSH_PULL;
    config.output_level = XMC_GPIO_OUTPUT_LEVEL_LOW;
    config.output_strength = XMC_GPIO_OUTPUT_STRENGTH_MEDIUM;

    /* Outputs LED */
    XMC_GPIO_Init(LED_1, &config);
    XMC_GPIO_Init(LED_2, &config);

    /* Buttons */
    config.mode = XMC_GPIO_MODE_INPUT_INVERTED_TRISTATE;
    config.output_level = XMC_GPIO_OUTPUT_LEVEL_HIGH;
    XMC_GPIO_Init(BUTTON_1, &config);
    XMC_GPIO_Init(BUTTON_2, &config);

    if(SysTick_Config(SYS_TICKS_1MS) != 0UL)
    {
        while(1U)
        {
        }
    }

    while(1U)
    {

    }
}

void SysTick_Handler(void)
{
    static uint32_t timer_led1 = 0UL;
    static uint32_t timer_led2 = 0UL;
    static uint32_t period_led1 = 1000UL;
    static uint32_t period_led2 = 100UL;


    if(++timer_led2 > period_led2)
    {
        timer_led2 = 0UL;
        LED2_TOGGEL;
    }

    if(READ_BUTTON1)
    {
        LED1_CLR;
        period_led1 = 2500UL;
        timer_led1 = 0UL;
    }

    /*
    if(++timer_led1 > period_led1)
    {
        timer_led1 = 0UL;
        LED1_TOGGEL;

        if(READ_BUTTON2)
            PRINT_TEXT;
    }
    */

    if(++timer_led1 > period_led1)
    {
        timer_led1 = 0UL;
        LED1_TOGGEL;

        if(READ_BUTTON2)
            PRINT_TEXT;
        else
            printf("Hello world!\n");
    }
}

/* Switch off pedantic checking */
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
