/****************************************************************************

 ****************************************************************************/
#ifndef __UI_NETWORK_CONFIG_LAN_H__
#define __UI_NETWORK_CONFIG_LAN_H__

//weather  area cont
#define NETWORK_LAN_ITEM_X         60
#define NETWORK_LAN_ITEM_Y         60//100
#define NETWORK_LAN_ITEM_W         (RIGHT_ROOT_W-2*NETWORK_LAN_ITEM_X)
#define NETWORK_LAN_ITEM_LW         300
#define NETWORK_LAN_ITEM_RW         (NETWORK_LAN_ITEM_W-NETWORK_LAN_ITEM_LW)
#define NETWORK_LAN_ITEM_H        50
#define NETWORK_LAN_ITEM_VGAP 8

//connect status text
#define NETWORK_LAN_CONNECT_STATUS_TEXTX (NETWORK_LAN_ITEM_X+NETWORK_LAN_ITEM_LW+NETWORK_LAN_ITEM_RW-NETWORK_CONNECT_STATUSW-NETWORK_CONNECT_STATUS_TEXTW-100)
#define NETWORK_LAN_CONNECT_STATUS_TEXTY (SYS_LEFT_CONT_H-NETWORK_CONNECT_STATUS_TEXTH-20)
#define NETWORK_LAN_CONNECT_STATUS_TEXTW 200
#define NETWORK_LAN_CONNECT_STATUS_TEXTH NETWORK_LAN_ITEM_H

//connect status
#define NETWORK_LAN_CONNECT_STATUSX (NETWORK_LAN_CONNECT_STATUS_TEXTX+NETWORK_LAN_CONNECT_STATUS_TEXTW)
#define NETWORK_LAN_CONNECT_STATUSY NETWORK_LAN_CONNECT_STATUS_TEXTY
#define NETWORK_LAN_CONNECT_STATUSW NETWORK_LAN_CONNECT_STATUS_TEXTW
#define NETWORK_LAN_CONNECT_STATUSH NETWORK_LAN_CONNECT_STATUS_TEXTH


#define IP_CTRL_LAN_CNT 9//10//9

#ifdef SUPPORT_PPPOE
#define LAN_CONFIG_MODE_TYPE_CNT 3
#else
#define LAN_CONFIG_MODE_TYPE_CNT 2
#endif
RET_CODE open_network_config_lan(u32 para1, u32 para2);
RET_CODE open_pppoe_connect(u32 para1, u32 para2);


#endif
