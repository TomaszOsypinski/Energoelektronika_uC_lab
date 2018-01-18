/**
 *******************************************************************************
 * @file    main.c
 * @version 0.1.1
 * @date    17.01.2018
 * @brief   Lab 01 - DTS.
 * @author  Tomasz Osypinski\n 
 *          e-mail: tomaszo@medcom.com.pl
 * @details Project name:\n
 *          Project number:\n
 *
 * Revision history:\n
 * \n
 * <b>version:  0.1.0</b>
 * date:        Jan 10, 2018\n
 * author:      Tomasz Osypinski\n
 * description: Working version\n
 * \n
 * <b>version:  0.1.1</b>
 * date:        17.01.2018\n
 * author:      Tomasz Osypinski\n
 * description: Added doxygen comments.\n
 *******************************************************************************
 */

/*
   O0 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1856       0    2072    3928     f58 Lab01_DTS.elf

   O0 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1820       0    2072    3892     f34 Lab01_DTS.elf

   O1 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1804       0    2072    3876     f24 Lab01_DTS.elf

   O1 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1800       0    2072    3872     f20 Lab01_DTS.elf

   O2 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1792       0    2072    3864     f18 Lab01_DTS.elf

   O2 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1796       0    2072    3868     f1c Lab01_DTS.elf

   O3 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1792       0    2072    3864     f18 Lab01_DTS.elf

   O3 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1796       0    2072    3868     f1c Lab01_DTS.elf
 */


/*
 *******************************************************************************
 * the includes
 *******************************************************************************
 */
#include "lab01_dts.h"

/* Switch on pedantic checking */
#if defined ( __GNUC__ )
#pragma GCC diagnostic warning "-pedantic"
#endif


 /*
 *******************************************************************************
 * #defines
 *******************************************************************************
 */
#define OPTIMIZE_LEVEL "O0"

#define SCENARIO_STRUCT (0)
#define SCENARIO_POS_AND_MASK (1)
#define SCENARIO 0

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
/**
 * Die temperature in [*C]
 */
volatile float die_temperature;

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
 *******************************************************************************
 * @brief   This routine is the application entry point. It is invoked by the
 *          device startup code.
 *******************************************************************************
 */
#if SCENARIO == SCENARIO_STRUCT
int __attribute__((optimize(OPTIMIZE_LEVEL))) main(void)
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
#elif SCENARIO == SCENARIO_POS_AND_MASK
int __attribute__((optimize(OPTIMIZE_LEVEL))) main(void)
{
    /* Initialization DTS */
    DTSCON |= ((uint32_t)(0x4UL << DTSCON_REFTRIM_Pos) |
               (uint32_t)(0x8UL << DTSCON_BGTRIM_Pos));
    DTSCON &= (uint32_t)~(DTSCON_PWD_Msk);

    /* Wait on ready of DTS */
    do
    {
    } while((DTSSTAT & DTSSTAT_RDY_Msk) == 0U);

    /* Start measure */
    DTSCON |= (uint32_t)DTSCON_START_Msk;

    while(1U)
    {
        do
        {

        } while((DTSSTAT & DTSSTAT_BUSY_Msk) != 0U);

        /* TDTS = (RESULT - 605) / 2.05 [°C]  */
        die_temperature = ((float)((DTSSTAT & DTSSTAT_RESULT_Msk) >> DTSSTAT_RESULT_Pos) - 605.0F) / 2.05F;
        /* Start measure */
        DTSCON |= (uint32_t)DTSCON_START_Msk;
    }
}
#else
#error "Define scenario (SCENARIO)!!!"
#endif
/* Switch off pedantic checking */
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
