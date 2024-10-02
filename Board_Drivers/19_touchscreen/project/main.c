#include "main.h"
#include "bsp_clk.h"
#include "bsp_led.h"
#include "bsp_delay.h"
#include "bsp_beep.h"
#include "bsp_key.h"
#include "bsp_int.h"
#include "bsp_exti.h"
#include "bsp_epit.h"
#include "bsp_keyfilter.h"
#include "bsp_uart.h"
#include "bsp_lcd.h"
#include "bsp_rtc.h"
#include "bsp_lcdapi.h"
#include "bsp_ap3216c.h"
#include "bsp_icm20608.h"
#include "bsp_ft5426.h"
#include "stdio.h"

 
/*
 * @description	: 使能I.MX6U的硬件NEON和FPU
 * @param 		: 无
 * @return 		: 无
 */
 void imx6ul_hardfpu_enable(void)
{
	uint32_t cpacr;
	uint32_t fpexc;

	/* 使能NEON和FPU */
	cpacr = __get_CPACR();
	cpacr = (cpacr & ~(CPACR_ASEDIS_Msk | CPACR_D32DIS_Msk))
		   |  (3UL << CPACR_cp10_Pos) | (3UL << CPACR_cp11_Pos);
	__set_CPACR(cpacr);
	fpexc = __get_FPEXC();
	fpexc |= 0x40000000UL;	
	__set_FPEXC(fpexc);
}

void lcd_draw_bigpoint(unsigned short x, unsigned short y ,unsigned int color)
{
	lcd_drawpoint(x, y, color);
	if(x < tftlcd_dev.width - 1){
		lcd_drawpoint(x+1, y, color);
	}

	if(y < tftlcd_dev.height - 1){
		lcd_drawpoint(x, y-1, color);
	}

	if((x < tftlcd_dev.width -1) && (y < tftlcd_dev.height -1)) {
		lcd_drawpoint(x + 1, y + 1,color);
	}
}

int main(void)
{
	unsigned char i = 0;
    unsigned char state = OFF;

    imx6ul_hardfpu_enable();    /* 开启硬件浮点运算及ENON */
    int_init();         //初始化中断
    imx6u_clkinit();    //初始化系统时钟
    delay_init();       //延时初始化
    uart_init();        //初始化串口
    clk_enable();       //使能外设时钟
    led_init();         //初始化LED
    beep_init();        //初始化峰鸣器
    key_init();         //初始化按键
    lcd_init();         //初始化LCD
    rtc_init();         //初始化时钟
    icm20608_init();    //初始化ICM20608
	ft5426_init();		//初始化FT5426  
	
	tftlcd_dev.forecolor = LCD_RED;
	lcd_show_string(50, 10, 400, 24, 24, (char*)"IMX6U-ZERO TOUCH SCREEN TEST");  
	lcd_show_string(50, 40, 200, 16, 16, (char*)"TOUCH SCREEN TEST");  
	lcd_show_string(50, 60, 200, 16, 16, (char*)"ATOM@ALIENTEK");  
	lcd_show_string(50, 80, 200, 16, 16, (char*)"2019/3/27");  

#if 0

 
	lcd_show_string(50, 110, 400, 16, 16,	(char*)"TP Num	:");  
	lcd_show_string(50, 130, 200, 16, 16,	(char*)"Point0 X:");  
	lcd_show_string(50, 150, 200, 16, 16,	(char*)"Point0 Y:");  
	lcd_show_string(50, 170, 200, 16, 16,	(char*)"Point1 X:");  
	lcd_show_string(50, 190, 200, 16, 16,	(char*)"Point1 Y:");  
	lcd_show_string(50, 210, 200, 16, 16,	(char*)"Point2 X:");  
	lcd_show_string(50, 230, 200, 16, 16,	(char*)"Point2 Y:");  
	lcd_show_string(50, 250, 200, 16, 16,	(char*)"Point3 X:");  
	lcd_show_string(50, 270, 200, 16, 16,	(char*)"Point3 Y:");  
	lcd_show_string(50, 290, 200, 16, 16,	(char*)"Point4 X:");  
	lcd_show_string(50, 310, 200, 16, 16,	(char*)"Point4 Y:");  
#endif
	tftlcd_dev.forecolor = LCD_BLUE;

	while(1)
{
#if 0
		
		
		lcd_shownum(50 + 72, 110, ft5426_dev.point_num , 1, 16);
		lcd_shownum(50 + 72, 130, ft5426_dev.x[0], 5, 16);
		lcd_shownum(50 + 72, 150, ft5426_dev.y[0], 5, 16);
		lcd_shownum(50 + 72, 170, ft5426_dev.x[1], 5, 16);
		lcd_shownum(50 + 72, 190, ft5426_dev.y[1], 5, 16);
		lcd_shownum(50 + 72, 210, ft5426_dev.x[2], 5, 16);
		lcd_shownum(50 + 72, 230, ft5426_dev.y[2], 5, 16);
		lcd_shownum(50 + 72, 250, ft5426_dev.x[3], 5, 16);
		lcd_shownum(50 + 72, 270, ft5426_dev.y[3], 5, 16);
		lcd_shownum(50 + 72, 290, ft5426_dev.x[4], 5, 16);
		lcd_shownum(50 + 72, 310, ft5426_dev.y[4], 5, 16);
#endif
	printf("x = %d, y = %d\r\n", ft5426_dev.x[0],ft5426_dev.y[0]);

	lcd_draw_bigpoint(ft5426_dev.x[0], ft5426_dev.y[0], LCD_RED);

		delay_ms(10);
		i++;
	
		if(i == 50)
		{	
			i = 0;
			state = !state;
			led_switch(LED0,state); 
		}
	}
    return 0;


}
