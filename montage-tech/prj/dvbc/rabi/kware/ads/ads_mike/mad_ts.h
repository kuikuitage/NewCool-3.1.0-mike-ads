/*
 * mad_ts.h
 *
 *  Created on: 2015-11-27
 */

#ifndef _MAD_TS_H_
#define _MAD_TS_H_

#define ENABLE_M_AD					1
#define ENABLE_M_AD_TS				1

#define MAD_DESCRIPTION_TABLE_ID	0x40
#define MAD_TS_PID					0x12
#define MAD_TIMEOUT					200000
#define MAD_TYPE_MAX				3

#define MAD_MAX_SECTION				100


typedef enum
{
	MAD_TS_TASK_STATE_IDLE,
	MAD_TS_TASK_STATE_INIT,
	MAD_TS_TASK_STATE_WAIT_DATA,
	MAD_TS_TASK_STATE_STOP,
	MAD_TS_TASK_STATE_NUM
} MAD_TS_TASK_STATE;


typedef struct _mad_type_info
{
	unsigned int table_id : 8;
	unsigned int mad_type : 8;
	unsigned int version_number : 32;
	unsigned int CRC32 : 32;
}MAD_TYPE_INFO;


typedef enum
{
	MAD_PARSE_STATE_NONE,
	MAD_PARSE_STATE_TIMEOUT,
	MAD_PARSE_STATE_ERROR,
	MAD_PARSE_STATE_FOUND_DESCRIPTION,
	MAD_PARSE_STATE_FOUND_DATA,
	MAD_PARSE_STATE_FINISH,
	MAD_PARSE_STATE_NUM
} MAD_PARSE_STATE;

typedef struct _mad_description_
{
	unsigned int mad_data_table_id :8;
	unsigned int mad_type :8;
	unsigned int platform_id :16;
	unsigned int customer_id :16;
	unsigned int model_id :16;
	char sn_start[32];
	char sn_end[32];
	unsigned char mac_start[6];
	unsigned char mac_end[6];
	unsigned int version_number :32;
	unsigned int reserved[2];
	unsigned int total_size :32;
	unsigned int section_size :16;
	unsigned int total_sec_count :16;
	unsigned int data_offeset :16;
	unsigned int reserved2 :16;
	unsigned int CRC32 :32; /* CRC32 check to make sure the data transmission is correct*/
} MAD_DESCRIPTION;


int mad_ts_task_init(void);
int start_monitor_mad(void);
int stop_monitor_mad(void);


#endif /* _MAD_TS_H_ */
