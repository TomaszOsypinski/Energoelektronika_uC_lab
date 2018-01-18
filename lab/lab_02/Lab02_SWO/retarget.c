/**
 *******************************************************************************
 * @file	retarget.c
 * @version 0.1.0
 * @date    12.01.2017
 * @brief	Retargeting stdio function _write
 * @author  Tomasz Osypinski\n 
 *			e-mail: tomaszo@medcom.com.pl
 * @details Project name:		\n
 * 			Project number: 	\n
 *
 * Revision history:			\n
 * 								\n
 * version: 	0.1.0			\n
 * date:		12.01.2017		\n
 * author:		Tomasz Osypinski\n
 * description:	Working version	\n
 *******************************************************************************
 */

/*
 *******************************************************************************
 * the includes
 *******************************************************************************
 */
#include <stdio.h>
#include <stdint.h>
#include <xmc_common.h>

 /*
 *******************************************************************************
 * #defines
 *******************************************************************************
 */

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
static void sendChar(const uint8_t *ptr);

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
 * @brief		Retargeting output of printf function on appropriate medium. See
 * 				sendChar().
 * @param		fd not used
 * @param		buf pointer to buffer with data
 * @param		count of data to send
 * @return		int
 *******************************************************************************
 */
int _write(int fd, const void *buf, size_t count)
{
	int CharCnt = 0;
	uint8_t * ptr = (uint8_t *)buf;

	/* Parameter is not used, suppress unused argument warning */
	(void)fd;

	while(count--)
	{
		sendChar(ptr);
		ptr++;
		CharCnt++;
	}
	return CharCnt;
}

/**
 *******************************************************************************
 * @brief	Send char on appropriate medium
 * @param	ptr pointer to char which will be send
 * @return	none
 *******************************************************************************
 */
static void sendChar(const uint8_t *ptr)
{
    ITM_SendChar((uint32_t)(*ptr));
}
