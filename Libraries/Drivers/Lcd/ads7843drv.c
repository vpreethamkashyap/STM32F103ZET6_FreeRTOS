						 //=========================================================================================================================================
#include <string.h>
#include "ads7843drv.h"
#include "stm32f10x.h"
//====================================================================================
void Delayus( int k)
{
    int j;
    for(j=k;j > 0;j--);    
}
//====================================================================================
void TP_Init(void)
{
  // IODIR1 = 0x00;
 //  IODIR1 = IODIR1 | MASK_CS | MASK_DCLK | MASK_DIN;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOG,  ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
       GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15|GPIO_Pin_13|GPIO_Pin_12;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;                 //ÍÆÍì
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
       GPIO_Init(GPIOB, &GPIO_InitStructure);

       GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 ;
       GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
       GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;
       GPIO_Init(GPIOG, &GPIO_InitStructure);
       //Read_X();
}
//====================================================================================
static void WR_CMD (unsigned char cmd) 
{
    unsigned char buf;
    unsigned char i;
    TP_CS(1);
    TP_DIN(0);
    TP_DCLK(0);
    TP_CS(0);
    for(i=0;i<8;i++) 
    {
        buf=(cmd>>(7-i))&0x1;
        TP_DIN(buf);
        Delayus(5);
        TP_DCLK(1);
        Delayus(5);
        TP_DCLK(0);
    }
}
//====================================================================================
static unsigned short RD_AD(void) 
{
    unsigned short buf=0,temp;
    unsigned char i;
    TP_DIN(0);
    TP_DCLK(1);
    for(i=0;i<12;i++) 
    {
        Delayus(5);
        TP_DCLK(0);         
        Delayus(5);   
        temp= (TP_DOUT) ? 1:0;
        buf|=(temp<<(11-i));
        
        Delayus(5);
        TP_DCLK(1);
    }
    TP_CS(1);
    buf&=0x0fff;
    return(buf);
}
//====================================================================================
int Read_X(void) 
{ 
    int i;
    WR_CMD(CHX);
   // while(TP_BUSY);
    Delayus(5);
    i=RD_AD();
    return i;   
}
//====================================================================================
int Read_Y(void) 
{ 
    int i;
    WR_CMD(CHY);
    //while(TP_BUSY);
    Delayus(5);
    i=RD_AD();
    return i;    
}
//====================================================================================
void TP_GetAdXY(int *x,int *y) 
{
    int adx,ady;
    adx=Read_X();
    ady=Read_Y();
    *x=adx;
    *y=ady;
}
