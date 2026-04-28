
#ifndef _HELIOS_LWIP_NETIF_H_
#define _HELIOS_LWIP_NETIF_H_

#include "netif.h"
#include "ip4_addr.h"

#if defined(PLAT_ASR)
typedef ip_addr_t ip4_addr_t;
#endif

typedef struct
{
    uint8_t *mac;
    char *hostname;
    struct
    {
        int iptype;
        ip_addr_t ipaddr;
        ip_addr_t netmask;
        ip_addr_t gw;
        ip_addr_t dns_server[2];
    } ipv4_info;
} Helios_Netif_Ipconfig_t;

typedef int (*helios_netif_eth_low_output_fn)(uint8_t *data, uint32_t len);
typedef int (*helios_netif_slip_low_output_fn)(uint8_t *data, uint32_t len);


// eth api
int helios_netif_eth_init(struct netif* netif);
int helios_netif_eth_add(struct netif* netif, uint8_t mac[6], ip4_addr_t *ip, ip4_addr_t *mask, ip4_addr_t *gw, netif_init_fn init, helios_netif_eth_low_output_fn output);
void helios_netif_eth_remove(struct netif* netif);
int helios_netif_eth_low_input(struct netif* netif, uint8_t *data, uint32_t len);

// slip api
int helios_netif_slip_init(struct netif* netif);
int helios_netif_slip_add(struct netif* netif, ip4_addr_t *ip, ip4_addr_t *mask, ip4_addr_t *gw, netif_init_fn init, helios_netif_slip_low_output_fn output);
void helios_netif_slip_remove(struct netif* netif);
int helios_netif_slip_low_input(struct netif* netif, uint8_t *data, uint32_t len);

// public api
int helios_netif_set_addr(struct netif* netif, ip4_addr_t *ip, ip4_addr_t *mask, ip4_addr_t *gw);
int helios_netif_set_dns(struct netif* netif, ip4_addr_t *pri, ip4_addr_t *sec);
int helios_netif_set_up(struct netif* netif);
int helios_netif_set_down(struct netif* netif);
int helios_netif_dhcp(struct netif* netif);
void helios_netif_ipconfig(struct netif* netif, Helios_Netif_Ipconfig_t *ipconfig);
int helios_netif_set_defult_nic(char *ip);
int helios_netif_set_nat(struct netif* netif, char *out_ip);

#endif
