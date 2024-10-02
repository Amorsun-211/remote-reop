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
#include "stdio.h"


int main(void)
{
    struct rtc_datetime datetime;
    //unsigned int color = 0;
    static unsigned char state = 0;
    unsigned char index = 0;

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


    tftlcd_dev.forecolor = LCD_RED; 
    tftlcd_dev.backcolor = LCD_WHITE;
    lcd_show_string(10,10,260,32,32,(char*)"APAH IMX6U");
    lcd_show_string(10,80,240,24,24,(char*)"RTC TEST");
    lcd_show_string(10,110,240,16,16,(char*)"ATOM&ALIENTEL");
    lcd_show_string(10,130,240,12,12,(char*)"2023/12/20 13:11");


    while(1) {
        rtc_getdatetime(&datetime);
        printf("当前时间：%d年%d月%d日:%d:%d:%d\r\n",datetime.year,datetime.month,datetime.day,
                datetime.hour,datetime.minute,datetime.second);
        state = !state;
        led_switch(LED0,state);
        delay_ms(1000);
    }
    return 0;
}