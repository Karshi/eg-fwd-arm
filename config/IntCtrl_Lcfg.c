/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl_Lcfg.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IntCtrl_Cfg.h"
#include "intctrl.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**
 * Create an array of desired interrupts to initialize
 * Struct format: { IRQn, EN(0|1), PRI(0-7) } 
 */
NVIC_ConfigType	NVIC_Config[]	=	
{
	{SYSTICK_IRQn, IRQn_ENABLE, IRQn_PRI_3}
};

/* Calculating the size of the array */
uint32_t	IRQn_count = sizeof(NVIC_Config)/ sizeof(NVIC_Config[0]);
/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Lcfg.c
 *********************************************************************************************************************/
