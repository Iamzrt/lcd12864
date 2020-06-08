/**
  ******************************************************************************
  * @file    	lcd12864.c
  * @author  	ZRT
  * @version 	V1.0
  * @date   	2019/12/30
  * @brief    HDG12864F-3
  ******************************************************************************  
  * 
  * 
  ******************************************************************************
  */

/*-- includes ----------------------------------------------------------------*/
#include "./lcd12864.h"


/*-- defined -----------------------------------------------------------------*/
#define            LCD_WIDTH                    128 
#define            LCD_HIGH                     64    

#define            LCD_LINE_DOT                 8



#define            LCD12864_E						         P2_3		  /* Enable clock input. */
#define            LCD12864_RW  								 P2_2			/* Signal select to read and write. */
#define            LCD12864_A0  								 P2_1			/* Control/Data select signal */
#define            LCD12864_REST								 P2_0			/* Reset signal. */

#define            LCD12864_DAT									 P0
#define            LCD12864_BUSY_BIT						 P0_7


static    void   delay_us(u8_t t);



#define            DELAY_US(us)						delay_us(us)


#define DISPLAY_ON()           lcd12864_write(OPS_COM, 0xaf)   // Display on, 显示开 
#define DISPLAY_OFF()          lcd12864_write(OPS_COM, 0xae)   // Display off,显示关



/*-- typedef -----------------------------------------------------------------*/
typedef    enum
{
  OPS_COM  =  (u8_t)0,
	OPS_DAT  =  1,
}DI_OpsType;



/*-- private variables -------------------------------------------------------*/





/*-- functions ---------------------------------------------------------------*/

static  void delay_us(u8_t t)
{
	while(t--);
}



/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static void lcd12864_check_busy(void)
{
  do
  {
	  LCD12864_E = 0;
    LCD12864_A0 = 0;
    LCD12864_RW = 1;   
		DELAY_US(10);	/* us */
    LCD12864_E = 1;
		DELAY_US(10);	/* us */
  }while(LCD12864_BUSY_BIT == 1);
}

/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
static  void  lcd12864_write(DI_OpsType type, u8_t dat)
{
  lcd12864_check_busy();

  LCD12864_E = 0;			/* Enable pin */

  LCD12864_RW = 0;    /* Write mode. */

	if(type == OPS_COM)
	{
    LCD12864_A0 = 0;  /* Instruction operation. */	
	}
	else if(type == OPS_DAT)
	{
    LCD12864_A0 = 1;    /* Data operation. */
	}

  DELAY_US(10);	/* us */

  LCD12864_DAT = dat;

  DELAY_US(10);	/* us */

  LCD12864_E = 1;   /* Start write data, rise edge to write data. */

  DELAY_US(10); /* Wait for write finish. */
}



/**           
  * @brief     LCD Line base address setting.       
  * @param    
  * @return  
  * @note
  */
static void lcd12864_set_page_address(u8_t addr)
{
  addr = 0xb0|addr;       
  lcd12864_write(OPS_COM, addr); /* Total page = 8 pages(lines) */
}



/**           
  * @brief     LCD column base address setting.       
	             列地址分成两部分（高四位和低四位）写入，显示 RAM 每访问一次，列地址自动加一
							 The column address is written in two parts (high four bits and low four bits), 
							 showing that the column address is automatically added to each RAM access
  * @param    
  * @return  
  * @note
  */
static void lcd12864_set_column_address(u8_t addr)
{
  lcd12864_write(OPS_COM, 0x10|(0x0f&(addr>>4)));  /* 取出高四位00001111. Take out the high four bits 00001111 */
  lcd12864_write(OPS_COM, 0x0f&addr);  /* 取出低四位. Take out the low four bits */
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void  lcd12864_init(void)
{
//  /* Reset the lcd */
//  LCD12864_REST = 0;
//  DELAY_US(3000);
  LCD12864_REST = 1;
//  DELAY_US(2000);

  /* Initialize. */
	lcd12864_write(OPS_COM, 0xc8);
	lcd12864_write(OPS_COM, 0xa1);
	lcd12864_write(OPS_COM, 0xa6);
	//DISPLAY_ON();
}



/**           
  * @brief      
  * @param    
  * @return  
  * @note
  */
void  lcd12864_clear_screen(u8_t value)
{
  u8_t i = 0;
	u8_t j = 0;

  for(i=0; i<(LCD_HIGH/LCD_LINE_DOT); i++)
  {
    lcd12864_set_page_address(i);
		lcd12864_set_column_address(0);
    for(j=0; j<LCD_WIDTH; j++)
		{
      lcd12864_write(OPS_DAT, value);
		}
  }
}


/**           
  * @brief            
  * @param    
  * @return  
  * @note
  */
void show_pic(u8_t* address)//显示图片函数
{                                         //address是是指向数组的指针，用法：show_Pic（XY）当中XY为数组名
  u8_t i,j,k; 

	lcd12864_write(OPS_COM, 0x34);        //打开扩展指令集
	i = 0x80;           
	for(j = 0;j < 32;j++)
	{
      lcd12864_write(OPS_COM, i++);
      lcd12864_write(OPS_COM, 0x80);	
  		for(k = 0 ;k < 16;k++)
  		{
  		    lcd12864_write(OPS_DAT, *address++);
  		}
		//ptr += 16;
		
	}
	i = 0x80; 
 	for(j = 0;j < 32;j++)
	{
 	   lcd12864_write(OPS_COM, i++);
     lcd12864_write(OPS_COM, 0x88);	 	  
  		for(k = 0 ;k < 16;k++)
  		{
   		    lcd12864_write(OPS_DAT, *address++);
   		} 
		//ptr += 16;
	}  
  lcd12864_write(OPS_COM, 0x36);        //打开绘图显示
	lcd12864_write(OPS_COM, 0x30);        //回到基本指令集

}

/*---------------------- end of file -----------------------------------------*/
