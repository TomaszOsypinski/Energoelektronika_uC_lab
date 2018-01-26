/**
 *******************************************************************************
 * @file    lab01_dts.h
 * @version 0.1.0
 * @date    Jan 17, 2018
 * @brief   Die Temperature Sensor of XMC4700 header file
 * @author  Tomasz Osypinski\n 
 *          e-mail: tomaszo@medcom.com.pl
 * @details Project name:\n
 *          Project number:\n
 *
 * Revision history:\n
 * \n
 * version:     0.1.0\n
 * date:        Jan 17, 2018\n
 * author:      Tomasz Osypinski\n
 * description: Working version\n
 *******************************************************************************
 */

#ifndef LAB01_DTS_H_
#define LAB01_DTS_H_

/*
 *******************************************************************************
 * the includes
 *******************************************************************************
 */
#include <stdint.h>
/**
 * @addtogroup LAB_01
 * @{
 */

/**
 * @addtogroup DTS
 * @brief Definition of Die Temperature Sensor of XMC4700
 * @{
 */

/*
 *******************************************************************************
 * #defines
 *******************************************************************************
 */
/**
 *  Base address of System Control Unit Registers
 */
#define BASE_ADDRES     (0x50004000UL)
/**
 * DTSCON Register Offset Address
 */
#define DTSCON_ADDRES   (BASE_ADDRES + 0x0000008CUL)
/**
 * DTSSTAT Register Offset Address
 */
#define DTSSTAT_ADDRES  (BASE_ADDRES + 0x00000090UL)
/**
 *  Access to DTSCON register
 */
#define DTSCON_REGISTER  (*((volatile uint32_t *)DTSCON_ADDRES))
/**
 *  Access to DTSSTAT register
 */
#define DTSSTAT_REGISTER (*((const volatile uint32_t *)DTSSTAT_ADDRES))

/* -----------------------------  SCU_GENERAL_DTSCON  ----------------------------- */
#define DTSCON_PWD_Pos            (0UL)                     /*!< SCU_GENERAL DTSCON: PWD (Bit 0)                             */
#define DTSCON_PWD_Msk            (0x1UL)                   /*!< SCU_GENERAL DTSCON: PWD (Bitfield-Mask: 0x01)               */
#define DTSCON_START_Pos          (1UL)                     /*!< SCU_GENERAL DTSCON: START (Bit 1)                           */
#define DTSCON_START_Msk          (0x2UL)                   /*!< SCU_GENERAL DTSCON: START (Bitfield-Mask: 0x01)             */
#define DTSCON_OFFSET_Pos         (4UL)                     /*!< SCU_GENERAL DTSCON: OFFSET (Bit 4)                          */
#define DTSCON_OFFSET_Msk         (0x7f0UL)                 /*!< SCU_GENERAL DTSCON: OFFSET (Bitfield-Mask: 0x7f)            */
#define DTSCON_GAIN_Pos           (11UL)                    /*!< SCU_GENERAL DTSCON: GAIN (Bit 11)                           */
#define DTSCON_GAIN_Msk           (0x1f800UL)               /*!< SCU_GENERAL DTSCON: GAIN (Bitfield-Mask: 0x3f)              */
#define DTSCON_REFTRIM_Pos        (17UL)                    /*!< SCU_GENERAL DTSCON: REFTRIM (Bit 17)                        */
#define DTSCON_REFTRIM_Msk        (0xe0000UL)               /*!< SCU_GENERAL DTSCON: REFTRIM (Bitfield-Mask: 0x07)           */
#define DTSCON_BGTRIM_Pos         (20UL)                    /*!< SCU_GENERAL DTSCON: BGTRIM (Bit 20)                         */
#define DTSCON_BGTRIM_Msk         (0xf00000UL)              /*!< SCU_GENERAL DTSCON: BGTRIM (Bitfield-Mask: 0x0f)            */

/* -----------------------------  DTSSTAT  ---------------------------- */
#define DTSSTAT_RESULT_Pos        (0UL)                     /*!< SCU_GENERAL DTSSTAT: RESULT (Bit 0)                         */
#define DTSSTAT_RESULT_Msk        (0x3ffUL)                 /*!< SCU_GENERAL DTSSTAT: RESULT (Bitfield-Mask: 0x3ff)          */
#define DTSSTAT_RDY_Pos           (14UL)                    /*!< SCU_GENERAL DTSSTAT: RDY (Bit 14)                           */
#define DTSSTAT_RDY_Msk           (0x4000UL)                /*!< SCU_GENERAL DTSSTAT: RDY (Bitfield-Mask: 0x01)              */
#define DTSSTAT_BUSY_Pos          (15UL)                    /*!< SCU_GENERAL DTSSTAT: BUSY (Bit 15)                          */
#define DTSSTAT_BUSY_Msk          (0x8000UL)                /*!< SCU_GENERAL DTSSTAT: BUSY (Bitfield-Mask: 0x01)             */

/*
 *******************************************************************************
 * typedefs
 *******************************************************************************
 */
/**
 * DTSCON register definition
 */
union DTSCON_REG
{
    uint32_t data;          /*!< Access to whole register */
    struct
    {
        uint32_t PWD     :1; /*!< This bit defines the DTS power state */
        uint32_t START   :1; /*!< This bit starts a measurement of the DTS */
        uint32_t rsvd0   :2; /*!< Reserved */
        uint32_t OFFSET  :7; /*!< Offset Calibration Value */
        uint32_t GAIN    :6; /*!< This bit field interfaces the gain calibration
                                  values tothe DTS. */
        uint32_t REFTRIM :3; /*!< This bit field interfaces the reference trim
                                  calibration values to the DTS. */
        uint32_t BGTRIM  :4; /*!< This bit field interfaces the bandgap trim
                                  calibration values to the DTS. */
        uint32_t rsvd1   :8;
    };
};

/**
 * DTSSTAT register definition
 */
union DTSSTAT_REG
{
    uint32_t data;
    struct
    {
        uint32_t RESULT :10;
        uint32_t rsvd0        :4;
        uint32_t RDY    :1;
        uint32_t BUSY   :1;
        uint32_t rsvd1        :16;
    };
};

struct DTS_REGS
{
    volatile union DTSCON_REG DTSCON;
    volatile const union DTSSTAT_REG DTSSTAT;
};


/*
 *******************************************************************************
 * globals
 *******************************************************************************
 */


/*
 *******************************************************************************
 * the function prototypes
 *******************************************************************************
 */
#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

/**
 * @}
 */

/**
 * @}
 */

#endif /* end of LAB01_DTS_H_ */
