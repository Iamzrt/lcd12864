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
#ifndef    LCD12864_H
#define    LCD12864_H




/*-- includes  ---------------------------------------------------------------*/
#include "../../includes/platform_conf.h"


/*-- defined  ---------------------------------------------------------------*/
        



/*-- typedef  ----------------------------------------------------------------*/




/*-- functions  ---------------------------------------------------------------*/
extern    void    lcd12864_init(void);
extern    void    lcd12864_clear_screen(u8_t value);
extern    void    show_pic(u8_t* address);

#endif   /* LCD12864_H */

/*---------------------- end of file -----------------------------------------*/
