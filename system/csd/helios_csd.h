/*================================================================
  Copyright (c) 2022, Quectel Wireless Solutions Co., Ltd. All rights reserved.
  Quectel Wireless Solutions Proprietary and Confidential.
=================================================================*/

typedef unsigned long UINT32;
typedef uint8_t uint8;

typedef enum 
{
    HELIOS_CSD_NONE =0,      // dialer at not init
    HELIOS_CSD_INITED,       // dialer at channel is prepared
    HELIOS_CSD_CONNECTING,   // dialer be calling
    HELIOS_CSD_CONNECTED,    // dialer connected
    HELIOS_CSD_DISCONNECTED, // dialer disconnected
    HELIOS_CSD_STATUS_MAX
}HELIOS_CSD_STATUS_E;


typedef void (*csd_recv_cb_t)(char * , UINT32);
typedef void (*csd_nofication_cb_t) (char * , UINT32);


/*****************************************************************
* Function: Helios_Csd_Init
*
* Description:
*	csd function init. 
*   will creat csd process task must init once.
* Parameters:
*       NULL
*
* Return:
* 	0			ok
*	-1 			error
*
*****************************************************************/
int Helios_Csd_Init(void);

/*****************************************************************
* Function: Helios_Csd_Modem_Config
*
* Description:
* 	csd modem config, csd must work on gsm mode.
* 
* Parameters:
* 	band_mode	  		[in] 	modem act: 0 auto 
									  	   1 gsm 
									       2 wcdma
									       3 lte
* 	
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
int Helios_Csd_Modem_Config(uint8 band_mode);


/*****************************************************************
* Function: Helios_Csd_Modem_Ims_Config
*
* Description:
* 	ims switch control, ims must close when use csd function. 
* 
* Parameters:
* 	mode	  		[in] 	0 off ims 
							1 on ims 
* 	
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
int Helios_Csd_Modem_Ims_Config(uint8 mode);

/*****************************************************************
* Function: Helios_Csd_Modem_Is_Ok
*
* Description:
* 	modem act is OK 
* 
* Parameters:
*  NULL
* 	
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
bool Helios_Csd_Modem_Is_Ok(void);


/*****************************************************************
* Function: Helios_Csd_Dialer_Connect
*
* Description:
* 	csd call number
* 
* Parameters:
*  dialer_num   [in]  eg:+123145646
* 	
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
int Helios_Csd_Dialer_Connect(char *dialer_num);

/*****************************************************************
* Function: Helios_Csd_Dialer_Reject
*
* Description:
* 	csd call reject
* 
* Parameters:
*  NULL
* 	
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
int Helios_Csd_Dialer_Reject(void);

/*****************************************************************
* Function: Helios_Csd_Dialer_Answer
*
* Description:
* 	csd call answer
* 
* Parameters:
*  NULL
* 	
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
int Helios_Csd_Dialer_Answer(void);

/*****************************************************************
* Function: Helios_Csd_Set_Recv_Callback
*
* Description:
* 	csd data recive callback register function.
* 
* Parameters:
*  recv_cb          [in]  app side data recv from modem function callback.
*  notification_cb  [in]  app side CSD link status recv from modem function callback. 
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
bool Helios_Csd_Set_Recv_Callback(csd_recv_cb_t recv_cb, csd_nofication_cb_t notification_cb);

/*****************************************************************
* Function: Helios_Csd_Send_Data
*
* Description:
* 	csd data send function.
* 
* Parameters:
*  buf          [in]  data send to modem side when csd is connected.
*  len          [in]  data len
*
* Return:
* 	0			ok
*	-1 			error

*
*****************************************************************/
int Helios_Csd_Send_Data(char *buf, UINT32 len);

/*****************************************************************
* Function: Helios_Csd_Get_Dialer_Status
*
* Description:
* get dialer status
* 
* Parameters:
* NULL
*
* Return:
* 	0			NONE
*	1			INITED
*	2			CONNECTING
*	3			CONNECTED
*	4           DISCONNECTED
*
*****************************************************************/
HELIOS_CSD_STATUS_E Helios_Csd_Get_Dialer_Status(void);

/*****************************************************************
* Function: Helios_Csd_Get_Ring_Cli_Status
*
* Description:
*  get clip indication status
* 
* Parameters:
* NULL
*
* Return:
* 	0			disable
*	1			enable
*
*****************************************************************/
uint8 Helios_Csd_Get_Ring_Cli_Status(void);

/*****************************************************************
* Function: Helios_Csd_Ring_Cli_Config
*
* Description:
*  set clip indication config
* 
* Parameters:
*  status          [in]  set clip indication mode
*
* Return:
* 	0			ok
*	else		error
*
*****************************************************************/
int Helios_Csd_Ring_Cli_Config(uint8 status);

/*****************************************************************
* Function: Helios_Csd_Get_Ring_Clcc_Info
*
* Description:
* get dialer status
* 
* Parameters:
* number          [in] inquery number by clcc command
*
* Return:
* 	0			ok
*	else	    error
*
*****************************************************************/
int Helios_Csd_Get_Ring_Clcc_Info(char *number);

