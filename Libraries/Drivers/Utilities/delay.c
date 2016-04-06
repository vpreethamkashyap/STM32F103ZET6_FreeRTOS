#include "delay.h"

void Delay(uint32_t t) {
  uint32_t j;
  for(;t>0;t--)
    {
      for(j=720000;j>0;j--);
    }

}
void delay_ms(uint32_t ms)
{
  vTaskDelay( ms / portTICK_RATE_MS );
}
