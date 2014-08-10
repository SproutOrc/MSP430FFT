/********************************************************************
//DM430-L型最小系统板外部资源配置文件Config.h
//包含板载各个资源的硬件配置，如果用户使用过程中，对应的硬件发生了更改，可利用该头文件更改使用
//SD/MMC卡初始化硬件配置未包含
//调试环境：EW430 V5.30
//作者：www.avrgcc.com
//时间：2014.03.01
********************************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <msp430x14x.h>

//延时函数，IAR自带，经常使用到
#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
//#define CPU_F ((double)32768)   //外部低频晶振32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0)) 
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0)) 

//自定义数据结构，方便使用
#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//8个LED灯，连接在P6口，可通过断开电源停止使用，ADC使用时断开电源
#define LED8DIR         P6DIR
#define LED8            P6OUT                             //P6口接LED灯，8个

//4个独立按键连接在P10~P13
#define KeyPort         P1IN                              //独立键盘接在P10~P13

//串口波特率计算，当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数
#define baud           9600                                //设置波特率的大小
#define baud_setting   (uint)((ulong)CPU_F/((ulong)baud))  //波特率计算公式
#define baud_h         (uchar)(baud_setting>>8)            //提取高位
#define baud_l         (uchar)(baud_setting)               //低位

//RS485控制管脚，CTR用于控制RS485处于收或者发状态
#define RS485_CTR1      P5OUT |= BIT2;          //控制线置高，RS485发送状态
#define RS485_CTR0      P5OUT &= ~BIT2;         //控制线置低，RS485接收状态

//2.8寸TFT彩屏显示控制相关硬件配置
#define RS_CLR	        P5OUT &= ~BIT5           //RS置低
#define RS_SET	        P5OUT |=  BIT5           //RS置高

#define RW_CLR	        P5OUT &= ~BIT6           //RW置低
#define RW_SET	        P5OUT |=  BIT6           //RW置高

#define RD_CLR	        P5OUT &= ~BIT7           //E置低
#define RD_SET	        P5OUT |=  BIT7           //E置高

#define CS_CLR	        P5OUT &= ~BIT0            //CS置低
#define CS_SET	        P5OUT |=  BIT0            //CS置高

#define RST_CLR	        P5OUT &= ~BIT3            //RST置低
#define RST_SET	        P5OUT |=  BIT3            //RST置高

#define LE_CLR	        P5OUT &= ~BIT1            //LE置低
#define LE_SET	        P5OUT |=  BIT1            //LE置高

//2.8寸TFT彩屏触摸屏控制相关硬件配置
#define PEN_CLR	        P2OUT &= ~BIT0           //PEN置低,触碰触摸屏时，Penirq引脚由未触摸时的高电平变为低电平
#define PEN_SET	        P2OUT |=  BIT0           //PEN置高
#define PEN             (P2IN & 0x01)            //P2.0输入的值

#define TPDO_CLR	P2OUT &= ~BIT1           //TPDO置低
#define TPDO_SET	P2OUT |=  BIT1           //TPDO置高
#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1输入的值

#define BUSY_CLR	P2OUT &= ~BIT3           //BUSY置低
#define BUSY_SET	P2OUT |=  BIT3           //BUSY置高

#define TPDI_CLR	P2OUT &= ~BIT4            //TPDI置低
#define TPDI_SET	P2OUT |=  BIT4            //TPDI置高

#define TPCS_CLR	P2OUT &= ~BIT5            //TPCS置低
#define TPCS_SET	P2OUT |=  BIT5            //TPCS置高

#define TPCLK_CLR	P2OUT &= ~BIT6            //TPCLK置低
#define TPCLK_SET	P2OUT |=  BIT6            //TPCLK置高

//彩屏/12864液晶/1602液晶的数据口，三液晶共用
#define DataDIR         P4DIR                     //数据口方向
#define DataPort        P4OUT                     //P4口为数据口

//12864/1602液晶控制管脚
#define RS_CLR	        P5OUT &= ~BIT5           //RS置低
#define RS_SET	        P5OUT |=  BIT5           //RS置高

#define RW_CLR	        P5OUT &= ~BIT6           //RW置低
#define RW_SET	        P5OUT |=  BIT6           //RW置高

#define EN_CLR	        P5OUT &= ~BIT7           //E置低
#define EN_SET	        P5OUT |=  BIT7           //E置高

#define PSB_CLR	        P5OUT &= ~BIT0            //PSB置低，串口方式
#define PSB_SET	        P5OUT |=  BIT0            //PSB置高，并口方式

//#define RST_CLR	        P5OUT &= ~BIT1            //RST置低
//#define RST_SET	        P5OUT |= BIT1             //RST置高

//12864应用指令集
#define CLEAR_SCREEN	0x01		          //清屏指令：清屏且AC值为00H
#define AC_INIT		0x02		          //将AC设置为00H。且游标移到原点位置
#define CURSE_ADD	0x06		          //设定游标移到方向及图像整体移动方向（默认游标右移，图像整体不动）
#define FUN_MODE	0x30		          //工作模式：8位基本指令集
#define DISPLAY_ON	0x0c		          //显示开,显示游标，且游标位置反白
#define DISPLAY_OFF	0x08		          //显示关
#define CURSE_DIR	0x14		          //游标向右移动:AC=AC+1
#define SET_CG_AC	0x40		          //设置AC，范围为：00H~3FH
#define SET_DD_AC	0x80                      //设置DDRAM AC
#define FUN_MODEK	0x36		          //工作模式：8位扩展指令集

//颜色代码，TFT显示用
#define White          0xFFFF           													//显示颜色代码
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

//NRF2401模块控制线
#define  RF24L01_CE_0        P1OUT &=~BIT5         //CE在P15         
#define  RF24L01_CE_1        P1OUT |= BIT5        

#define  RF24L01_CSN_0       P2OUT &=~BIT7         //CS在P27
#define  RF24L01_CSN_1       P2OUT |= BIT7     

#define  RF24L01_SCK_0       P3OUT &=~BIT3         //SCK在P33
#define  RF24L01_SCK_1       P3OUT |= BIT3   

#define  RF24L01_MISO_0      P3OUT &=~BIT2         //MISO在P32
#define  RF24L01_MISO_1      P3OUT |= BIT2

#define  RF24L01_MOSI_0      P3OUT &=~BIT1         //MOSI在P31
#define  RF24L01_MOSI_1      P3OUT |= BIT1

#define  RF24L01_IRQ_0       P1OUT &=~BIT4         //IRQ在P14     
#define  RF24L01_IRQ_1       P1OUT |= BIT4

//DS18B20控制脚，单脚控制
#define DQ_IN	        P1DIR &= ~BIT7		  //设置输入，DS18B20接单片机P53口
#define DQ_OUT	        P1DIR |= BIT7		  //设置输出
#define DQ_CLR	        P1OUT &= ~BIT7	          //置低电平
#define DQ_SET	        P1OUT |= BIT7	          //置高电平
#define DQ_R	        P1IN & BIT7		  //读电平

//红外接收头H1838控制脚，单脚控制
#define RED_IN	        P1DIR &= ~BIT6	          //设置输入，红外接收头接单片机PE3口
#define RED_OUT	        P1DIR |=  BIT6	          //设置输出
#define RED_L	        P1OUT &= ~BIT6	          //置低电平
#define RED_H	        P1OUT |= BIT6             //置高电平
#define RED_R	        (P1IN & BIT6)	          //读电平

//***********************************************************************
//                   系统时钟初始化，外部8M晶振
//***********************************************************************
void Clock_Init();

//***********************************************************************
//                   系统时钟初始化，内部RC晶振
//***********************************************************************
void Clock_Init_Inc();

//***********************************************************************
//                   系统时钟初始化，外部32.768K晶振
//***********************************************************************
void Clock_Init_Ex32768();

//***********************************************************************
//               MSP430内部看门狗初始化
//***********************************************************************
void WDT_Init();

#endif
