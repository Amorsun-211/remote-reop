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
#include "stdio.h"


int main(void)
{
    int a, b;
    int c = 100;

    int_init();         //初始化中断
    imx6u_clkinit();    //初始化系统时钟
    delay_init();       //延时初始化
    uart_init();        //初始化串口
    clk_enable();       //使能外设时钟
    led_init();         //初始化LED
    beep_init();        //初始化峰鸣器
    key_init();         //初始化按键


    printf("%d的十六进制为：%#x\r\n", c, c);
    while(1) {
        printf("请输入两个整数，使用空格隔开:");
        scanf("%d %d", &a, &b);
        printf("\r\n 数据%d+%d=%d\r\n", a, b, a+b);
    }
    return 0;
    
}