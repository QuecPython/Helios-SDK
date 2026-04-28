#ifndef _HELIOS_NW_H
#define _HELIOS_NW_H

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _ipsec_local_conf_t {
	char *wan_ip;
	char *sub_ip;
	char *aes;
	char *sha1;
	unsigned int spi;
	int port;
} Helios_IPSEC_Local_Param_t;
typedef struct _ipsec_remote_conf_t {
	char *pub_ip;
	char *sub_ip;
	char *aes;
	char *sha1;
	unsigned int spi;
	int port;
} Helios_IPSEC_Remote_Param_t;

typedef struct _ipsec_conf_t {
	Helios_IPSEC_Local_Param_t local;
	Helios_IPSEC_Remote_Param_t remote;
} Helios_IPSEC_Param_t;


int helios_ipsec_vpn(Helios_IPSEC_Param_t *ipsec_conf);

void helios_ipsec_vpn_deinit();

#ifdef __cplusplus
}
#endif

#endif