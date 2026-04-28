#ifndef _QL_UART_SLIP_H_
#define _QL_UART_SLIP_H_
#include "helios_uart.h"

typedef enum  {
		HELIOS_SLIP_INNER,    // as inner network card with esp ap mode 
		HELIOS_SLIP_OUTER     // as outer network card with esp station mode
} Helios_Slip_Work_Mode;

/*****************************************************************
* Function: slip_netif_construct
*
* Description:
* 	construct slip netif network card
* 
* Parameters:
*  port          [in]  uart port choose
*  type          [in]  work mode 
*  external_ip   [in]  set default network card by network ip
*
* Return:
* 	0			ok
*	else 	    error

*
*****************************************************************/
int Helios_Slip_Netif_Construct(Helios_UARTNum port, Helios_Slip_Work_Mode type, unsigned int external_ip);


/*****************************************************************
* Function: Helios_Get_Slip_Ipconfig
*
* Description:
* 	get slip ipconfig info
* 
* Parameters:
*	ipconfig          [in]  ipconfig array, 0/1/2/3 indicate ip/netmask/gw/mtu
* Return:
*	0			ok
*	else 	    error
*****************************************************************/
int Helios_Get_Slip_Ipconfig(unsigned int *ipconfig);


/*****************************************************************
* Function: Helios_Slip_Netif_Destroy
*
* Description:
* 	close slip network card
* 
* Parameters:
*
* Return:
*
*****************************************************************/
void Helios_Slip_Netif_Destroy();

/*****************************************************************
* Function: Helios_Slip_Netif_NICSetDNS
*
* Description:
* 	get slip ipconfig info
* 
* Parameters:
*	pri_str          [in]  pri dns
*	sec_str          [in]  second dns
* Return:
*	0			ok
*	else 	    error
*****************************************************************/
int Helios_Slip_Netif_NICSetDNS(char *pri_str, char *sec_str);

/*****************************************************************
* Function: Helios_Slip_Config
*
* Description:
* 	uart config before using, special for bt flow choose
* 
* Parameters:
*	flow          [in]  enum, 0/1 flow enable/disable
* Return:
*	0			ok
*	else 	    error
*****************************************************************/
int Helios_Slip_Config(int flow);

int Helios_Slip_Set_Default_NIC(uint32_t ip);

#endif
