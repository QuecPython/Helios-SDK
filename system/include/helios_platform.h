#ifndef __HELIOS_PLATFORM_H__
#define __HELIOS_PLATFORM_H__

typedef enum
{
  CLK_32K = 0,
  CLK_MAX,
}HELIOS_CLK_E;


typedef enum
{
  DISABLE = 0,
  ENABLE,
}HELIOS_CTL_E;

extern int helios_clk_output(unsigned char pin_number,HELIOS_CLK_E clk,unsigned char flag);


#endif

