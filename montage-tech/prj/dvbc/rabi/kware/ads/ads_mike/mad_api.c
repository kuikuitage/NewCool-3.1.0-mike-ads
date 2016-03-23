#include "ui_common.h"
#include "mtos_mutex.h"
#include "mad_type.h"
#include "mad_api.h"

GSOS_Mutex_t GSOS_MutexCreate(unsigned int prio)
{
	void * p_mutex = NULL;
	if(0 != prio)
	{
		p_mutex = mtos_mutex_create(prio);
	}
	return (GSOS_Mutex_t)p_mutex;
}

void GSOS_MutexDelete(GSOS_Mutex_t lock)
{
	if(NULL != lock)
		MT_ASSERT(mtos_mutex_delete(lock) == TRUE);
	return;
}

void GSOS_MutexLock(GSOS_Mutex_t lock)
{
	if(NULL != lock)
		MT_ASSERT(mtos_mutex_take(lock) == TRUE);
	return;
}

void GSOS_MutexUnlock(GSOS_Mutex_t lock)
{
	if(NULL != lock)
		MT_ASSERT(mtos_mutex_give(lock) == TRUE);
	return;
}

GSOS_TaskHandle_t GSOS_TaskCreate(PFNTHREAD mad_ts_task, int argcnt, void* args, u32 nstksize, u32 *pstk, u32 nprio, u8* p_taskname/*"MAD TS"*/)
{
	BOOL b = FALSE;
	if(NULL != mad_ts_task && 0 != nstksize && NULL != pstk)
		b = mtos_task_create(p_taskname,mad_ts_task,args,nprio,pstk,nstksize);
	return (b == FALSE) ? NULL : (GSOS_TaskHandle_t)mad_ts_task;
}
void GSOS_TaskDelay(int sleep)
{
	MT_ASSERT(sleep >= 0);
	return  mtos_task_sleep((u32)sleep);
}


static int getFindStrCount(char* src, char* find){  
    int count = 0;  
    char* position =src;  
    int findLen = strlen(find);  
    while((position = strstr(position, find)) != NULL){  
        count++;  
        position = position + findLen;  
    }  
    return count;  
} 

/*
 *Replace all the param2 to param3 from string src
 */
char* str_replace_all(char* src, char* find, char* replaceWith){  
    if(find == NULL || replaceWith == NULL){  
        return strdup(src);  
    }  
    char* afterReplaceHead = NULL;  
    char* afterReplaceIndex = NULL;  
    int count = 0;  
    int i,j,k;  
      
    int srcLen = strlen(src);  
    int findLen = strlen(find);  
    int replaceWithLen = strlen(replaceWith);  
      
    char* srcIndex = src;  
    int cpStrStart = 0;  
     
    count = getFindStrCount(src, find);  
    if(count == 0){  
        return strdup(src);  
    }  
      
    afterReplaceHead = afterReplaceIndex = (char*)malloc(srcLen + 1 + (replaceWithLen - findLen) * count);  
    memset(afterReplaceHead, '\0',sizeof(afterReplaceHead));  
  
    for(i = 0,j = 0,k = 0;i!=srcLen;i++){  
        if(src[i] == find[j]){  
            if(j == 0){  
                k = i;  
            }  
            if(j == (findLen-1)){  
                j = 0;  
                strncpy(afterReplaceIndex, srcIndex, i - findLen - cpStrStart + 1);  
                afterReplaceIndex = afterReplaceIndex + i - findLen - cpStrStart + 1;  
                srcIndex = srcIndex + i - findLen - cpStrStart + 1;  
                cpStrStart = i + 1;               
  
                strncpy(afterReplaceIndex, replaceWith, replaceWithLen);  
                afterReplaceIndex = afterReplaceIndex + replaceWithLen;  
                srcIndex = srcIndex + findLen;  
            }else{  
                j++;  
            }  
        }else{  
            if(j != 0){  
                i = k;  
            }  
            j = 0;  
        }  
    }  
    strncpy(afterReplaceIndex, srcIndex, i - cpStrStart);  
      
    return afterReplaceHead;  
} 
