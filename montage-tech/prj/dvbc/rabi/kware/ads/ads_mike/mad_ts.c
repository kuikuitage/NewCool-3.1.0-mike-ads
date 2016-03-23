#if ENABLE_M_AD
#include "mad.h"
#include "mad_type.h"
#include "mad_api.h"

#if ENABLE_M_AD_TS
#include "mad_ts.h"
#endif

#define INVALID_TASK 		NULL
#define INVALID_MUTEX 		NULL
#define GENDMX_BAD_CHANNEL 	0x1FFF

static GSOS_TaskHandle_t	mad_ts_task_id = INVALID_TASK;
static GSOS_Mutex_t 		mad_ts_mutex = INVALID_MUTEX;
static MAD_TS_TASK_STATE 	mad_ts_task_state = MAD_TS_TASK_STATE_IDLE;

//static MAD_TYPE_INFO mad_type_info[MAD_TYPE_MAX];
static int chn_mad_index = GENDMX_BAD_CHANNEL;
static MAD_PARSE_STATE mad_parse_state = MAD_PARSE_STATE_NONE;

//static MAD_DESCRIPTION *mad_description = NULL;
static MAD_DESCRIPTION mad_description;
static U8 *mad_content_data = NULL;

static U32 mad_section_got_count = 0;
static U32 mad_section_got_map_size = 0;
static U8 *mad_section_got_map;

//static U8 mad_type_count = 0;


/***********************************************************************************
 *                                   get & set                                     *
 ***********************************************************************************/
//-------------------- parse state --------------------
static int get_mad_parse_state(void)
{
	return mad_parse_state;
}

static void set_mad_parse_state(int new_state)
{
	mad_parse_state = new_state;
}


static MAD_DESCRIPTION *get_mad_description(void)
{
	return &mad_description;
}

//-------------------- got map --------------------
static void free_mad_section_got_map(void)
{
	if (mad_section_got_map)
	{
		GSOS_Free(mad_section_got_map);
		mad_section_got_map = NULL;
		mad_section_got_map_size = 0;
	}
}

static void reset_mad_got_section_count(void)
{
	mad_section_got_count = 0;
	if (mad_section_got_map && mad_section_got_map_size)
	{
		memset(mad_section_got_map, 0, mad_section_got_map_size);
	}
}

static BOOL alloc_mad_section_got_map(void)
{
	MAD_DESCRIPTION *mad_description = get_mad_description();

	if (!mad_description)
	{
		return FALSE;
	}
	free_mad_section_got_map();
	mad_section_got_map_size = (mad_description->total_sec_count + 7) / 8;//ALIGN(8)
	mad_section_got_map = (U8 *)GSOS_Malloc(mad_section_got_map_size);
	if (mad_section_got_map == NULL)
	{
		return FALSE;
	}
	reset_mad_got_section_count();

	return TRUE;
}

static BOOL is_mad_section_has_got(int section_num)
{
	int sec_num_byte = section_num >> 3;	// mad_section_num / 8
	int sec_num_bit = section_num & 7;		// mad_section_num % 8
	int section_max_num = 0;

	if (get_mad_description())
	{
		section_max_num = (get_mad_description())->total_sec_count;
	}
	if (mad_section_got_map && section_num < section_max_num)
	{
		if (mad_section_got_map[sec_num_byte] & (1 << sec_num_bit))
		{
			return TRUE;
		}
	}
	return FALSE;
}

static void set_mad_section_has_got(int section_num)
{
	int sec_num_byte = section_num >> 3;	// mad_section_num / 8
	int sec_num_bit = section_num & 7;		// mad_section_num % 8
	int section_max_num = 0;

	if (get_mad_description())
	{
		section_max_num = (get_mad_description())->total_sec_count;
	}
	if (mad_section_got_map && section_num < section_max_num)
	{
		if (!is_mad_section_has_got(section_num))
		{
			mad_section_got_count++;
		}
		mad_section_got_map[sec_num_byte] = (mad_section_got_map[sec_num_byte] | (0x01 << sec_num_bit));
	}
}

static int get_mad_got_section_count(void)
{
	return mad_section_got_count;
}

//-------------------- content data --------------------
static void free_mad_content_data(void)
{
	if (mad_content_data != NULL)
	{
		GSOS_Free(mad_content_data);
		mad_content_data = NULL;
	}
}

static BOOL alloc_mad_content_data(void)
{
	MAD_DESCRIPTION *mad_description = get_mad_description();

	free_mad_content_data();
	if (mad_description == NULL)
	{
		return FALSE;
	}

	MAD_INF("mad content data total size:%d\n", mad_description->total_size);
	mad_content_data = GSOS_Malloc(mad_description->total_size);
	if (mad_content_data == NULL)
	{
		return FALSE;
	}
	memset(mad_content_data, 0, mad_description->total_size);

	return TRUE;
}

static U8* get_mad_content_data(void)
{
	return mad_content_data;
}


/***********************************************************************************
 *                                section request                                  *
 ***********************************************************************************/
static BOOL is_mad_description_table_id(int table_id)
{
	return table_id == MAD_DESCRIPTION_TABLE_ID;
}

static BOOL save_mad_description_data(U8 *data, int length)
{
	MAD_DESCRIPTION *mad_description = get_mad_description();

	if (mad_description == NULL)
	{
		return FALSE;
	}
	if (length != sizeof(MAD_DESCRIPTION))
	{
		return FALSE;
	}
	memcpy(mad_description, data, length);

	return TRUE;
}


static BOOL is_mad_content_data_table_id(int table_id)
{
	MAD_DESCRIPTION *mad_description = get_mad_description();

	if (mad_description && mad_description->mad_data_table_id == table_id)
	{
		return TRUE;
	}
	return FALSE;
}

static BOOL save_mad_content_data(int section_num, U8 *data, int length)
{
	int offset;
	MAD_DESCRIPTION *description;
	U8 *content_data;

	description = get_mad_description();
	content_data = get_mad_content_data();
	if (is_mad_section_has_got(section_num))
	{
		return TRUE;
	}
	if (content_data == NULL)
	{
		return FALSE;
	}
	if (section_num < description->total_sec_count - 1)
	{
		offset = section_num * length;
	}
	else
	{
		offset = description->total_size - length; //the last section length maybe smaller than others
	}
	if (offset + length > description->total_size)
	{
		return FALSE;
	}
	memcpy(content_data + offset, data, length);
	set_mad_section_has_got(section_num);

	return TRUE;
}


BOOL is_got_all_mad_content_data_section(void)
{
	MAD_DESCRIPTION *description;

	description = get_mad_description();
	return get_mad_got_section_count() >= description->total_sec_count;
}

static BOOL SlotIndexIsValid(int chn_index)
{
	return TRUE;
}
static void FreeSectionSlot(int chn_index)
{
	return NULL;
}

static void free_mad_request(void)
{
	if (SlotIndexIsValid(chn_mad_index))
	{
		FreeSectionSlot(chn_mad_index);
		chn_mad_index = GENDMX_BAD_CHANNEL;
	}
}

static int get_sec_len(char* buf)
{
	if(buf != NULL)
		return strlen(buf)
}

BOOL CheckCRC32(char* inbuf,int secLen)
{
	return TRUE;
}
static MAD_PARSE_STATE parse_mad_section(unsigned char *section_buffer)
{
	int mad_section_length;
	int mad_section_num;
	int mad_objects_length;

	int offset = 0;
	int sec_table_id = -1;
	MAD_PARSE_STATE mad_parse_state = MAD_PARSE_STATE_NONE;


	mad_section_length = get_sec_len(section_buffer);
	mad_objects_length = mad_section_length - 12; // the real section data
	mad_section_num = (section_buffer[3] << 8) | section_buffer[4];

	if (CheckCRC32(section_buffer, mad_section_length) == 0)
	{
		MAD_ERR("%s crc error!\n", __FUNCTION__);
		return mad_parse_state;
	}

	sec_table_id = section_buffer[0]; //save the sec_table_id;
	section_buffer += 8;  // the section head before the real data is 8 bytes

	if (is_mad_description_table_id(sec_table_id))
	{
		MAD_INF("find mad description data!\n");
		if (save_mad_description_data(section_buffer, mad_objects_length))
		{
			mad_parse_state = MAD_PARSE_STATE_FOUND_DESCRIPTION;
		}
		else
		{
			mad_parse_state = MAD_PARSE_STATE_ERROR;
		}
	}
	else if (is_mad_content_data_table_id(sec_table_id))
	{
		MAD_INF("find mad content data!\n");
		if (save_mad_content_data(mad_section_num, section_buffer, mad_objects_length))
		{
			mad_parse_state = MAD_PARSE_STATE_FOUND_DATA;
			if (is_got_all_mad_content_data_section())
			{
				MAD_INF("got all mad content data!!\n");
				mad_parse_state = MAD_PARSE_STATE_FINISH;
			}
		}
		else
		{
			mad_parse_state = MAD_PARSE_STATE_ERROR;
		}
	}
	else
	{
		mad_parse_state = MAD_PARSE_STATE_ERROR;
	}

	return mad_parse_state;
}


static BOOL need_free_mad_request(MAD_PARSE_STATE mad_state)
{
	BOOL need_free = FALSE;

	switch (mad_state)
	{
		case MAD_PARSE_STATE_ERROR:
		case MAD_PARSE_STATE_TIMEOUT:
		case MAD_PARSE_STATE_FINISH:
		case MAD_PARSE_STATE_FOUND_DESCRIPTION:
			need_free = TRUE;
			break;
		default:
			break;
	}
	return need_free;
}

SIE_STATUS_T mad_parse_action(UINT8 reason, MAD_PARSE_STATE mad_state)
{
	MAD_INF("reason:0x%02X, state:%d\n", reason, mad_state);

	if ((reason & SIE_REASON_FILTER_TIMEOUT))
	{
		MAD_WRN("func:%s, sie filter timeout.\n", __FUNCTION__);
		set_mad_parse_state(MAD_PARSE_STATE_TIMEOUT);
	}
	else
	{
		set_mad_parse_state(mad_state);
	}

	if (need_free_mad_request(get_mad_parse_state()))
	{
		free_mad_request();
		return SIE_FREED;
	}

	return SIE_STARTED;
}

static SIE_STATUS_T mad_section_callback(UINT16 pid, struct si_filter_t *filter, UINT8 reason, UINT8 *sec_buffer, INT32 length)
{
	MAD_PARSE_STATE mad_state = MAD_PARSE_STATE_NONE;

	if (sec_buffer && length > 0)
	{
		mad_state = parse_mad_section(sec_buffer);
	}
	return mad_parse_action(reason, mad_state);
}

int SectionAllocSlot(mad_filter_callback callback,BOOL bl,int timeout,U16 pid);
{
	return 0x33;//temp value
}

BOOL SectionAllocFilter(int chn_index, U8* match, U8* mask, BOOL flag, BOOL mut_sec_flag)
{
	return TRUE;
}

BOOL SectionSlotSetPid(int chn_index,U16 pid)
{
	return TRUE;
}

int start_request_mad_data(U16 pid, int table_id)
{
	U8 mad_filter_match[16] = {0};
	U8 mad_filter_mask[16] = {0};
	BOOL multi_section = TRUE;
	int chn_mad_index_value = -1;

	if (is_mad_description_table_id(table_id))
	{
		multi_section = FALSE;
	}
	if (pid == DEMUX_INVALID_PID)
		return -1;

	if (SlotIndexIsValid(chn_mad_index))
	{
		return chn_mad_index;
	}

	memset(mad_filter_match, 0, sizeof(mad_filter_match));
	memset(mad_filter_mask, 0, sizeof(mad_filter_mask));
	mad_filter_match[0] = table_id; //the table id used in makeAD is 50
	mad_filter_mask[0] = 0xff;

#if(PLATFORM_SUPPORT == ALI_PLATFORM)
	//chn_mad_index = SectionAllocSlot(mad_section_callback, NULL, MAD_TIMEOUT, GS_FILTER_OTA, pid);
#elif (PLATFORM_SUPPORT == MSTAR_PLATFORM)
	//chn_mad_index = SectionAllocSlot(mad_section_callback, OTATimeOut, MAD_TIMEOUT, GS_FILTER_OTA);
#elif(PLATFORM_SUPPORT == NewCool_PLATFORM)
	chn_mad_index = SectionAllocSlot(mad_section_callback,NULL,MAD_TIMEOUT,pid);
#endif
	MAD_INF("[%s:%d] table_id:%d, chn_mad_index:%d.\n",__FUNCTION__, __LINE__, table_id, chn_mad_index);

	chn_mad_index_value = chn_mad_index;
	if (!SlotIndexIsValid(chn_mad_index))
	{
		return -1;
	}
	//use the slot allocated above and mad_filter_match, mad_filter_mask to configure the filter
	if (SectionAllocFilter(chn_mad_index, mad_filter_match, mad_filter_mask, FALSE/*TRUE*/, multi_section) < 0)
	{
		free_mad_request();
		return -1;
	}
	//enable the filter and begin to get data
	if (SectionSlotSetPid(chn_mad_index, pid) < 0)
	{
		free_mad_request();
		return -1;
	}
	
	return chn_mad_index_value;
}


static void start_fetch_mad_description(void)
{
	free_mad_request();
//	alloc_mad_description();
	start_request_mad_data(MAD_TS_PID, MAD_DESCRIPTION_TABLE_ID);
	set_mad_parse_state(MAD_PARSE_STATE_NONE);
}

static void start_fetch_mad_content_data(void)
{
	MAD_DESCRIPTION *mad_description;

	mad_description = get_mad_description();
	if (mad_description == NULL)
	{
		return;
	}
	MAD_INF("mad content data table id:%d\n", mad_description->mad_data_table_id);
	free_mad_request();
	alloc_mad_content_data();
	alloc_mad_section_got_map();
	start_request_mad_data(MAD_TS_PID, mad_description->mad_data_table_id);
	set_mad_parse_state(MAD_PARSE_STATE_NONE);
}


/***********************************************************************************
 *                                  check update                                   *
 ***********************************************************************************/
static BOOL is_mad_need_update(MAD_DESCRIPTION *mad_description)
{
	MAD_INF("mad type %d old version is:%d, current version is:%d\n", mad_description->mad_type,
			mad_get_content_version(mad_description->mad_type), mad_description->version_number);
	return !is_same_with_current_version(mad_description->mad_type, mad_description->version_number);
}


/***********************************************************************************
 *                                   handle data                                   *
 **********************************************************************************/
typedef struct _mad_data_string_type_map_
{
	char *string;
	int type;
} MAD_DATA_STRING_TYPE_MAP;

static int get_data_type_by_string(const char *string)
{
	int i;
	int data_type = MAD_DATA_TYPE_NUM;
	MAD_DATA_STRING_TYPE_MAP mad_data_string_type_map[] =
	{
		{"jpg", MAD_DATA_TYPE_JPG},
		{"m2v", MAD_DATA_TYPE_IFRAME},
	};

	for (i = 0; i < sizeof(mad_data_string_type_map) / sizeof(mad_data_string_type_map[0]); i++)
	{
		if (strcmp(string, mad_data_string_type_map[i].string) == 0)
		{
			data_type = mad_data_string_type_map[i].type;
			break;
		}
	}
	return data_type;
}

static BOOL parse_mad_ts_content_data(MAD_DESCRIPTION *mad_description, U8 *mad_content)
{
	cJSON *root = NULL;
	BOOL result = TRUE;
	char *ad_id;
	char *data_format;
	MAD_ITEM *item;
	int data_type;

	root = parse_mad_json_data(mad_content, mad_description->data_offeset);
	if (!root)
	{
		result = FALSE;
		goto EXIT;
	}
	if (!get_json_item_string_value(&ad_id, root, "ad_id"))
	{
		result = FALSE;
		goto EXIT;
	}

	item = new_mad_item_if_not_exsit(ad_id);
	if (!item)
	{
		result = FALSE;
		goto EXIT;
	}
	if (!get_json_item_string_value(&data_format, root, "fmt"))
	{
		result = FALSE;
		goto EXIT;
	}
	item->type = mad_description->mad_type;
	data_type = get_data_type_by_string(data_format);
	set_mad_item_data(item, data_type, mad_content + mad_description->data_offeset, mad_description->total_size - mad_description->data_offeset);
	if (mad_description->mad_type == MAD_TYPE_BOOT)
	{
		MAD_INF("start save boot ad into flash!\n");
		save_all_boot_ad_into_flash();
		delete_boot_ad_from_memory();
	}
	mad_set_content_version(mad_description->mad_type, mad_description->version_number);

EXIT:
	if (root)
	{
		cJSON_Delete(root);
	}

	return result;
}

static int handle_mad_content_data(MAD_DESCRIPTION *mad_description, U8 *mad_content)
{
	return parse_mad_ts_content_data(mad_description, mad_content);
}


/***********************************************************************************
 *                                     cleanup                                     *
 ***********************************************************************************/
static void mad_ts_cleanup(void)
{
	free_mad_request();
	free_mad_content_data();
	free_mad_section_got_map();
}


/***********************************************************************************
 *                                   mad ts task                                   *
 ***********************************************************************************/
static void set_mad_ts_task_state(int new_state)
{
	if (mad_ts_mutex == INVALID_MUTEX)
	{
		return;
	}
	GSOS_MutexLock(&mad_ts_mutex);
	mad_ts_task_state = new_state;
	GSOS_MutexUnlock(&mad_ts_mutex);
}

static void mad_ts_task(U32 argc, void *argv)
{
	MAD_TS_TASK_STATE new_state = MAD_TS_TASK_STATE_NUM;
	const unsigned int CHECK_UPDATE_INTERVAL = 30*1000;	//30s
	int sleep_time = CHECK_UPDATE_INTERVAL;

	while (1)
	{
		GSOS_MutexLock(&mad_ts_mutex);
		switch (mad_ts_task_state)
		{
			case MAD_TS_TASK_STATE_IDLE:
				sleep_time = CHECK_UPDATE_INTERVAL;
				break;
			case MAD_TS_TASK_STATE_INIT:
				start_fetch_mad_description();
				new_state = MAD_TS_TASK_STATE_WAIT_DATA;
				sleep_time = 100;
				break;
			case MAD_TS_TASK_STATE_WAIT_DATA:
				switch (get_mad_parse_state())
				{
					case MAD_PARSE_STATE_FOUND_DESCRIPTION:
						if (is_mad_need_update(get_mad_description()))
						{
							MAD_INF("version changed, need update ts mad now!!\n");
							start_fetch_mad_content_data();
						}
						else
						{
							MAD_INF("version is same, no need update mad!!\n");
							mad_ts_cleanup();
							sleep_time = CHECK_UPDATE_INTERVAL;
							new_state = MAD_TS_TASK_STATE_INIT;
						}
						break;
					case MAD_PARSE_STATE_FINISH:
						handle_mad_content_data(get_mad_description(), get_mad_content_data());
						//no break
					case MAD_PARSE_STATE_TIMEOUT:
					case MAD_PARSE_STATE_ERROR:
						mad_ts_cleanup();
						sleep_time = CHECK_UPDATE_INTERVAL;
						new_state = MAD_TS_TASK_STATE_INIT;
						break;
				}
				break;
			case MAD_TS_TASK_STATE_STOP:
				mad_ts_cleanup();
				new_state = MAD_TS_TASK_STATE_IDLE;
				break;
			default:
				break;
		}
		GSOS_MutexUnlock(&mad_ts_mutex);

		if (new_state != MAD_TS_TASK_STATE_NUM)
		{
			MAD_INF("mad ts task new state:%d\n", new_state);
			set_mad_ts_task_state(new_state);
		}
		if (mad_ts_task_state == MAD_TS_TASK_STATE_WAIT_DATA)
		{
			MAD_INF("mad ts parse state:%d\n", get_mad_parse_state());
		}
		new_state = MAD_TS_TASK_STATE_NUM;
		GSOS_TaskDelay(sleep_time);
	}
}


int start_monitor_mad(void)
{
	set_mad_ts_task_state(MAD_TS_TASK_STATE_INIT);

	return 0;
}

int stop_monitor_mad(void)
{
	if (mad_ts_mutex == INVALID_MUTEX)
	{
		return -1;
	}
	GSOS_MutexLock(&mad_ts_mutex);
	mad_ts_cleanup();
	GSOS_MutexUnlock(&mad_ts_mutex);

	set_mad_ts_task_state(MAD_TS_TASK_STATE_STOP);

	return 0;
}


int mad_ts_task_init(void)
{
	if (mad_ts_mutex == INVALID_MUTEX)
	{
		GSOS_MutexCreate(&mad_ts_mutex, ""/*"MAD TS"*/);
	}
	if (mad_ts_task_id == INVALID_TASK)
	{
		mad_ts_task_id = GSOS_TaskCreate((PFNTHREAD)mad_ts_task, 0, NULL, MAD_TASK_STACK_SIZE, NULL, MAD_TASK_PRIORITY, ""/*"MAD TS"*/);
	}
	if (mad_ts_task_id == INVALID_TASK)
	{
		MAD_ERR("create mad ts task fail!\n");
		return FALSE;
	}
	return TRUE;
}

#endif	/* ENABLE_M_AD_TS */
