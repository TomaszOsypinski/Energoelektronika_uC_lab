/**
 *******************************************************************************
 * @file    main.c
 * @version 0.1.0
 * @date    Jan 10, 2018
 * @brief   Enter brief Description of this module.
 * @author  Tomasz Osypinski\n 
 *          e-mail: tomaszo@medcom.com.pl
 * @details Project name:\n
 *          Project number:\n
 *
 * Revision history:\n
 * \n
 * version:     0.1.0\n
 * date:        Jan 10, 2018\n
 * author:      Tomasz Osypinski\n
 * description: Working version\n
 *******************************************************************************
 */

/*
 *******************************************************************************
 * the includes
 *******************************************************************************
 */
/* #include <xmc_common.h> */
#include <stdint.h>

/* Switch on pedantic checking */
/*
#if defined ( __GNUC__ )
#pragma GCC diagnostic warning "-pedantic"
#endif
*/

 /*
 *******************************************************************************
 * #defines
 *******************************************************************************
 */

typedef union DTSCON_REG
{
    uint32_t data;
    struct
    {
        uint32_t PWD     :1;
        uint32_t START   :1;
        uint32_t rsvd0   :2;
        uint32_t OFFSET  :7;
        uint32_t GAIN    :6;
        uint32_t REFTRIM :3;
        uint32_t BGTRIM  :4;
        uint32_t rsvd1   :8;
    };
} DTSCON_REG_t;

typedef union DTSSTAT_REG
{
    uint32_t data;
    struct
    {
        const uint32_t RESULT :10;
        uint32_t rsvd0        :4;
        const uint32_t RDY    :1;
        const uint32_t BUSY   :1;
        uint32_t rsvd1        :16;
    };
} DTSSTAT_REG_t;

#define BASE_ADDRES     (0x50004000UL)
#define DTSCON_ADDRES   (BASE_ADDRES + 0x0000008CUL)
#define DTSSTAT_ADDRES  (BASE_ADDRES + 0x00000090UL)
#define DTSCON  (*((volatile uint32_t *)DTSCON_ADDRES))
#define DTSSTAT (*((const volatile uint32_t *)DTSSTAT_ADDRES))
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
volatile float die_temperaure;

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
/**

 * @brief main() - Application entry point
 *
 * <b>Details of function</b><br>
 * This routine is the application entry point. It is invoked by the device startup code.
 */

volatile float die_temperature;
int main(void)
{
    DTSCON_REG_t dtscon_reg = {.data = 0UL};
    DTSSTAT_REG_t dtsstat_reg = {.data = 0UL};

    /* Initialization DTS */
    dtscon_reg.PWD = 0U;
    dtscon_reg.REFTRIM = 4U;
    dtscon_reg.BGTRIM = 8U;
    DTSCON = dtscon_reg.data;

    /* Wait on ready of DTS */
    do
    {
        dtsstat_reg.data = DTSSTAT;
    } while(!(dtsstat_reg.RDY));

    /* Start measure */
    dtscon_reg.START = 1U;
    DTSCON = dtscon_reg.data;

    while(1U)
    {
        do
        {
            dtsstat_reg.data = DTSSTAT;
        } while((dtsstat_reg.BUSY));

        /* TDTS = (RESULT - 605) / 2.05 [°C]  */
        die_temperature = ((float)dtsstat_reg.RESULT - 605.0F) / 2.05F;
        /* Start measure */
        dtscon_reg.START = 1U;
        DTSCON = dtscon_reg.data;
    }
}

/* Switch off pedantic checking */
/*
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
*/
