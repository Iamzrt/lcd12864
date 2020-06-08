/**
  ******************************************************************************
  * @file    
  * @author  
  * @version 
  * @date   
  * @brief   
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */
#ifndef  PLATFORM_CONFIG_H
#define  PLATFORM_CONFIG_H


/* C++支持 */
#ifdef __cplusplus
extern "C" {
#endif


/* 平台选择，只能选其一 */
//#define    N76E003_PLATFORM 
//#define    MS51XB9AE_PLATFORM
#define    AT89C5X_PLATFORM


/*-- includes ----------------------------------------------------------------*/ 
#include <rtx51tny.h>
#include "../../includes/_sys_std.h"


#define     TASK_DEF(func, id)   void  func##_task(void)  _task_  id

#define     TASK_CREATE(handle, id, param)		os_create_task(id)

#define     TASK_DELETE(handle, id)		        os_delete_task(id)

#define     TASK_WAIT_TIME(time)                os_wait(K_TMO, time, 0)

#define     TASK_WAIT_SIGNAL(signal)            os_wait(K_SIG, 0, 0)

#define     TASK_SWITCH()                       os_switch_task()

#define     TASK_SEND_SIGNAL(id)                os_send_signal(id)
   
#define     TASK_ISR_SEND_SIGNAL(id)            isr_send_signal(id)

#define     TASK_CLEAR_SIGNAL(id)               os_clear_signal(id)

/*-- Configurations ----------------------------------------------------------*/

#if defined(N76E003_PLATFORM)


#define     FOSC_160000

#include "../portable/N76E003/N76E003.h"
#include "../portable/N76E003/SFR_Macro.h"
#include "../portable/N76E003/Function_define.h"  

#elif defined(MS51XB9AE_PLATFORM)


#include "../portable/MS51XB9XE/MS51_16K.h"
//#include "../portable/MS51XB9XE/Function_Define_MS51_16K.h"

//#include "../portable/MS51XB9XE/Common.h"
//#include "../portable/MS51XB9XE/delay.h"
//#include "../portable/MS51XB9XE/eeprom.h"
//#include "../portable/MS51XB9XE/eeprom_sprom.h"
//#include "../portable/MS51XB9XE/IAP.h"
//#include "../portable/MS51XB9XE/IAP_SPROM.h"
//#include "../portable/MS51XB9XE/sys.h"

#elif defined(AT89C5X_PLATFORM)

#include <REGX55.H>

  
#endif



#ifdef __cplusplus
}
#endif

#endif    /* PLATFORM_CONFIG_H */

/*------------------ end of file ---------------------------------------------*/
