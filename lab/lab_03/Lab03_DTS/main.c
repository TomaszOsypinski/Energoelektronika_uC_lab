/**
 *******************************************************************************
 * @file    main.c
 * @version 0.1.1
 * @date    26.01.2018
 * @brief   Lab 03 - DTS.
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
 * \n
 * <b>version:  0.1.2</b>
 * date:        26.01.2018\n
 * author:      Tomasz Osypinski\n
 * description: Added new scenario SCENARIO_STRUCT_MAPPED_ON_PER_MEM\n
 *******************************************************************************
 */

/*
   O0 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1856       0    2072    3928     f58 Lab01_DTS.elf

   O0 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1820       0    2072    3892     f34 Lab01_DTS.elf

   O0 - SCENARIO_STRUCT_MAPPED_ON_PER_MEM
   text     data     bss     dec     hex filename
   1836       8    2072    3916     f4c Lab03_DTS.elf

   O1 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1804       0    2072    3876     f24 Lab01_DTS.elf

   O1 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1800       0    2072    3872     f20 Lab01_DTS.elf

   O1 - SCENARIO_STRUCT_MAPPED_ON_PER_MEM
   text    data     bss     dec     hex filename
   1808       8    2072    3888     f30 Lab03_DTS.elf

   O2 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1792       0    2072    3864     f18 Lab01_DTS.elf

   O2 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1796       0    2072    3868     f1c Lab01_DTS.elf

   O2 - SCENARIO_STRUCT_MAPPED_ON_PER_MEM
   text    data     bss     dec     hex filename
   1804       8    2072    3884     f2c Lab03_DTS.elf

   O3 - SCENARIO_STRUCT
   text    data     bss     dec     hex filename
   1792       0    2072    3864     f18 Lab01_DTS.elf

   O3 - POS_AND_MASK
   text    data     bss     dec     hex filename
   1796       0    2072    3868     f1c Lab01_DTS.elf

   O3 - SCENARIO_STRUCT_MAPPED_ON_PER_MEM
   text    data     bss     dec     hex filename
   1804       8    2072    3884     f2c Lab03_DTS.elf
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
#define SCENARIO_STRUCT_MAPPED_ON_PER_MEM (2)
#define SCENARIO 2

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
    union DTSCON_REG dtscon= {.data = 0UL};
    union DTSSTAT_REG dtsstat = {.data = 0UL};

    /* Initialization DTS */
    dtscon.PWD = 0U;
    dtscon.REFTRIM = 4U;
    dtscon.BGTRIM = 8U;
    DTSCON_REGISTER = dtscon.data;

    /* Wait on ready of DTS */
    do
    {
        dtsstat.data = DTSSTAT_REGISTER;
    } while(!(dtsstat.RDY));

    /* Start measure */
    dtscon.START = 1U;
    DTSCON_REGISTER = dtscon.data;

    while(1U)
    {
        do
        {
            dtsstat.data = DTSSTAT_REGISTER;
        } while((dtsstat.BUSY));

        /* TDTS = (RESULT - 605) / 2.05 [°C]  */
        die_temperature = ((float)dtsstat.RESULT - 605.0F) / 2.05F;
        /* Start measure */
        dtscon.START = 1U;
        DTSCON_REGISTER = dtscon.data;
    }
}
#elif SCENARIO == SCENARIO_POS_AND_MASK
int __attribute__((optimize(OPTIMIZE_LEVEL))) main(void)
{
    /* Initialization DTS */
    DTSCON &= (uint32_t)~(DTSCON_PWD_Msk);
    DTSCON |= ((uint32_t)(0x4UL << DTSCON_REFTRIM_Pos) |
               (uint32_t)(0x8UL << DTSCON_BGTRIM_Pos));

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
#elif SCENARIO == SCENARIO_STRUCT_MAPPED_ON_PER_MEM
/* In TI this global structure is defined in F2837xS_GlobalVariableDefs.c
 * F2837xS Global Variables */
struct DTS_REGS __attribute__((section (".DtsRegsFile"))) DTS;
int __attribute__((optimize(OPTIMIZE_LEVEL))) main(void)
{
    /* Initialization DTS */
    DTS.DTSCON.PWD = 0U;
    DTS.DTSCON.REFTRIM = 4U;
    DTS.DTSCON.BGTRIM = 8U;

    /* Wait on ready of DTS */
    do
    {
    } while(!(DTS.DTSSTAT.RDY));

    /* Start measure */
    DTS.DTSCON.START = 1U;

    while(1U)
    {
        do
        {

        } while((DTS.DTSSTAT.BUSY));

        /* TDTS = (RESULT - 605) / 2.05 [°C]  */
        die_temperature = ((float)DTS.DTSSTAT.RESULT - 605.0F) / 2.05F;
        /* Start measure */
        DTS.DTSCON.START = 1U;
    }
}
#else
#error "Define scenario (SCENARIO)!!!"
#endif


/* Switch off pedantic checking */
#if defined ( __GNUC__ )
#pragma GCC diagnostic pop
#endif
