#ifndef __MAD_TYPE_H__
#define __MAD_TYPE_H__
#include "mad_type.h"
#include "sys_types.h"
#define PLATFORM_SUPPORT 	NewCool_PLATFORM

#ifndef UINT8
#define UINT8  unsigned char
#endif
#ifndef UINT16
#define UINT16 unsigned short
#endif
#ifndef UINT32
#define UINT32 unsigned long
#endif
#ifndef INT32
#define INT32 signed int
#endif

typedef handle_t 	GSOS_TaskHandle_t;
typedef void*		GSOS_Mutex_t;


#define 	GSOS_Malloc		SY_MALLOC
#define 	GSOS_Free		SY_FREE

#define 	DEMUX_INVALID_PID 0x1FFF

#define 	SIE_REASON_FILTER_TIMEOUT	0xFF 

enum{
	ALI_PLATFORM,
	MSTAR_PLATFORM,
	NewCool_PLATFORM,
};

typedef enum{
	SIE_STARTED,
	SIE_FREED,
}SIE_STATUS_T;

#endif	//__MAD_TYPE_H__

