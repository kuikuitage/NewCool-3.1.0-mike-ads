#ifndef __MADS_API_H__
#define __MADS_API_H__

#include "mad_type.h"

typedef SIE_STATUS_T(*mad_filter_callback)(UINT16 pid, handle_t filter, UINT8 reason, UINT8 *sec_buffer, INT32 length);
typedef void (*PFNTHREAD)(void *argv);

GSOS_Mutex_t GSOS_MutexCreate(unsigned int prio);

void GSOS_MutexDelete(GSOS_Mutex_t lock);

void GSOS_MutexLock(GSOS_Mutex_t lock);

void GSOS_MutexUnlock(GSOS_Mutex_t lock);

GSOS_TaskHandle_t GSOS_TaskCreate(PFNTHREAD mad_ts_task, int argcnt, void* args, u32 nstksize, u32 *pstk, u32 nprio, u8* p_taskname/*"MAD TS"*/);

void GSOS_TaskDelay(int sleep_time);

char* str_replace_all(char* src, char* find, char* replaceWith);

#endif //__MADS_API_H__
