/*
 * mad.c
 *
 *  Created on: 2015-4-2
 *      Author: Brant
 */

//#include "usifext.h"
//#include "http_common.h"
//#include "net_api.h"

#if ENABLE_M_AD

//#include "cJSON.h"
#include "mad.h"
#include "mad_interface.h"
#include "mad_api.h"


/***********************************************************************************
 *                               m-ad global define                                *
 ***********************************************************************************/
#define MAD_HEADER				("M-AD")
static U32 content_version[MAD_TYPE_NUM];


/***********************************************************************************
 *                           heart beat and version                                *
 ***********************************************************************************/
BOOL mad_set_content_version(int type, U32 version)
{
	if (type >= MAD_TYPE_NUM)
	{
		return FALSE;
	}
	content_version[type] = version;

	return TRUE;
}

U32 mad_get_content_version(int type)
{
	if (type >= MAD_TYPE_NUM)
	{
		return 0;
	}
	return content_version[type];
}

BOOL is_same_with_current_version(int type, U32 version)
{
	if (type >= MAD_TYPE_NUM)
	{
		return TRUE;
	}
	return content_version[type] == version;
}


/***********************************************************************************
 *                                     crc                                         *
 ***********************************************************************************/
#define MAD_GET_CRC32_POLY 0x04c11db7     /* AUTODIN II, Ethernet, & FDDI */

static U32 mad_get_crc32(U8 *data, int length)
{
	U32 crc32_table[256];
	int i, j;
	unsigned int c;
	unsigned int crc;
	U8 *p;

	for (i = 0; i < 256; ++i)
	{
		for (c = i << 24, j = 8; j > 0; --j)
			c = c & 0x80000000 ? (c << 1) ^ MAD_GET_CRC32_POLY : (c << 1);
		crc32_table[i] = c;
	}

	crc = 0xffffffff;
	for (p = data; length > 0; ++p, --length)
		crc = (crc << 8) ^ crc32_table[(crc >> 24) ^ *p];

	return crc;
}


/***********************************************************************************
 *                                    json                                         *
 ***********************************************************************************/
cJSON* parse_mad_json_data(char *data, int len)
{
	char *json_string = NULL;
	cJSON *root = NULL;

	if ((json_string = SY_MALLOC(len + 1)) == NULL)
	{
		MAD_ERR("%s no enough memory!!\n", __FUNCTION__);
		return NULL;
	}
	memset(json_string, 0, len + 1);
	memcpy(json_string, data, len);
	root = cJSON_Parse(json_string);
	if (NULL == root)
	{
		MAD_ERR("parse fail, bad json data!!\n%s\n", json_string);
	}
	SY_FREE(json_string);

	return root;
}


static void print_json_node(cJSON *node)
{
	char *json_string;

	if (!node)
	{
		printf("json node is NULL!\n");
		return;
	}
	json_string = cJSON_Print(node);
	if (json_string)
	{
		printf("%s\n", json_string);
		SY_FREE(json_string);
	}
}

BOOL get_json_item_num_value(double *value, cJSON *obj, const char *string)
{
	cJSON *item;

	item = cJSON_GetObjectItem(obj, string);
	if (!item)
	{
		MAD_WRN("no such item named %s!\n", string);
		print_json_node(obj);
		return FALSE;
	}
	if (item->type != cJSON_Number)
	{
		MAD_WRN("invalid data type of %s, its type is:%d\n", string, item->type);
		return FALSE;
	}
	*value = item->valuedouble;
	return TRUE;
}

BOOL get_json_item_string_value(char **value, cJSON *obj, const char *string)
{

	cJSON *item;

	item = cJSON_GetObjectItem(obj, string);
	if (!item)
	{
		MAD_WRN("no such item named %s!\n", string);
		print_json_node(obj);
		return FALSE;
	}
	if (item->type != cJSON_String)
	{
		MAD_WRN("invalid data type of %s, its type is:%d\n", string, item->type);
		return FALSE;
	}
	*value = item->valuestring;
	return TRUE;
}


/***********************************************************************************
 *                               m-ad item list                                    *
 ***********************************************************************************/
static MAD_ITEM* get_mad_list_head(void)	/* mad list head is not a valid item */
{
	static MAD_ITEM *mad_list_head = NULL;

	if (mad_list_head == NULL)
	{
		mad_list_head = (MAD_ITEM *)SY_FREE(sizeof(MAD_ITEM));
		if (mad_list_head)
		{
			memset(mad_list_head, 0, sizeof(MAD_ITEM));
		}
	}
	return mad_list_head;
}

static MAD_ITEM* new_mad_item(void)
{
	MAD_ITEM *item;

	item = SY_MALLOC(sizeof(MAD_ITEM));
	if (item)
	{
		memset(item, 0, sizeof(MAD_ITEM));
	}
	return item;
}

static void delete_mad_item(MAD_ITEM *item)
{
	if (item)
	{
		if (item->extra_data)
		{
			SY_FREE(item->extra_data);
		}
		if (item->content.data_addr)
		{
			SY_FREE(item->content.data_addr);
		}
		SY_FREE(item);
	}
}

static void set_mad_item_id(MAD_ITEM *item, const char *id)
{
	if (item)
	{
		snprintf(item->id, MAD_ID_SIZE, "%s", id);
	}
}

BOOL set_mad_item_data(MAD_ITEM *item, int data_type, U8 *data, int length)
{
	if (!item)
	{
		return FALSE;
	}
	if (item->content.data_addr)
	{
		SY_FREE(item->content.data_addr);
	}
	item->content.data_addr = SY_MALLOC(length);
	if (!item->content.data_addr)
	{
		return FALSE;
	}
	memcpy(item->content.data_addr, data, length);
	item->content.data_type = data_type;
	item->content.data_length = length;
	item->content.crc32 = mad_get_crc32(data, length);

	return TRUE;
}

#if ENABLE_DEBUG_MAD
void print_mad_item_list(void)
{
	MAD_ITEM *item_node;

	item_node = get_mad_list_head()->next;
	printf("mad list head");
	while (item_node)
	{
		printf("->0x%08x", item_node);
		item_node = item_node->next;
	}
	printf("\n");
}
#endif

/*
 * add mad item into list tail
 * if item already exist(use same id),do nothing.
 */
static void mad_list_add_item(MAD_ITEM *item)
{
	MAD_ITEM *item_node;

	item_node = get_mad_list_head();
	while (item_node->next)
	{
		if (memcmp(item_node->id, item->id, sizeof(item->id)) == 0)
		{
			return;
		}
		item_node = item_node->next;
	}
	item_node->next = item;
}

static MAD_ITEM* find_mad_item_by_id(const char *id)
{
	MAD_ITEM *item_node = NULL;

	item_node = get_mad_list_head()->next;
	while (item_node)
	{
		if (memcmp(item_node->id, id, strlen(id)) == 0)
		{
			return item_node;
		}
		item_node = item_node->next;
	}

	return NULL;
}

static MAD_ITEM* find_next_mad_item(MAD_ITEM *current)
{
	MAD_ITEM *item_node = NULL;

	if (!current)
	{
		return NULL;
	}
	item_node = get_mad_list_head();
	while (item_node)
	{
		if (current == item_node)
		{
			return item_node->next;
		}
		item_node = item_node->next;
	}
	return NULL;
}

static BOOL mad_item_match_type(MAD_ITEM *item, int type)
{
	if (item && item->type == type)
	{
		return TRUE;
	}
	return FALSE;
}

void delete_boot_ad_from_memory(void)
{
	MAD_ITEM *item_node_prev = NULL;
	MAD_ITEM *item_node = NULL;

	item_node_prev = get_mad_list_head();
	item_node = item_node_prev->next;
	while (item_node)
	{
		if (mad_item_match_type(item_node, MAD_TYPE_BOOT))
		{
			item_node_prev->next = item_node->next;
			delete_mad_item(item_node);
		}
		else
		{
			item_node_prev = item_node;
		}
		item_node = item_node_prev->next;
	}
}

void reset_all_mad_item_in_use_flag(void)
{
	MAD_ITEM *item_node;

	item_node = get_mad_list_head()->next;
	while (item_node)
	{
		{
			item_node->in_use = FALSE;
		}
		item_node = item_node->next;
	}
}

void delete_all_unused_mad_item(void)
{
	MAD_ITEM *item_node_prev = NULL;
	MAD_ITEM *item_node = NULL;

	item_node_prev = get_mad_list_head();
	item_node = item_node_prev->next;
	while (item_node)
	{
		MAD_INF("item 0x%08x in use:%d\n", item_node, item_node->in_use);
		if (!item_node->in_use)
		{
			item_node_prev->next = item_node->next;
			delete_mad_item(item_node);
		}
		else
		{
			item_node_prev = item_node;
		}
		item_node = item_node_prev->next;
	}
}

MAD_ITEM* new_mad_item_if_not_exsit(char *id)
{
	MAD_ITEM *item;

	item = find_mad_item_by_id(id);
	if (!item)
	{
		item = new_mad_item();
		if (item)
		{
			set_mad_item_id(item, id);
			mad_list_add_item(item);
		}
	}

	return item;
}


/***********************************************************************************
 *                              save/load boot ad                                  *
 ***********************************************************************************/
static MAD_ITEM* data_array_to_mad_item(U8 *data, int total_len)
{
	int index = 0;
	MAD_ITEM *item = NULL;
	U32 item_crc32 = 0;

	item = new_mad_item();
	if (item == NULL)
	{
		MAD_WRN("create mad item fail!\n");
		goto EXIT;
	}
	/* check flash start code */
	if (memcmp(data, MAD_HEADER, strlen(MAD_HEADER)) != 0)
	{
		MAD_WRN("bad magic number\n");
		goto EXIT;
	}
	index += 4;

	/* load m-ad item */
	memcpy(item->id, data + index, MAD_ID_SIZE);
	index += MAD_ID_SIZE;
	memcpy(&(item->type), data + index, sizeof(item->type));
	index += sizeof(item->type);
	memcpy(&(item->extra_data_length), data + index, sizeof(item->extra_data_length));
	index += sizeof(item->extra_data_length);
	if (item->extra_data_length > 0)
	{
		item->extra_data = SY_MALLOC(item->extra_data_length);
		if (item->extra_data == NULL)
		{
			goto EXIT;
		}
		memcpy(item->extra_data, data + index, item->extra_data_length);
	}
	index += item->extra_data_length;

	/* load content data */
	memcpy(&(item->content.data_type), data + index, sizeof(item->content.data_type));
	index += sizeof(item->content.data_type);
	memcpy(&(item->content.data_length), data + index, sizeof(item->content.data_length));
	index += sizeof(item->content.data_length);
	if (item->content.data_length > 0)
	{
		item->content.data_addr = SY_MALLOC(item->content.data_length);
		if (item->content.data_addr == NULL)
		{
			goto EXIT;
		}
		memcpy(item->content.data_addr, data + index, item->content.data_length);
	}
	index += item->content.data_length;
	/* load content data crc32 and check */
	memcpy(&(item->content.crc32), data + index, sizeof(item->content.crc32));
	if (mad_get_crc32(item->content.data_addr, item->content.data_length) != item->content.crc32)
	{
		MAD_WRN("content crc32 check fail!\n");
		goto EXIT;
	}
	index += sizeof(item->content.crc32);

	/* load and check item crc32 */
	memcpy(&item_crc32, data + index, sizeof(item_crc32));
	if (item_crc32 != mad_get_crc32(data, index))
	{
		MAD_WRN("item crc32 check fail!\n");
		goto EXIT;
	}
	index += sizeof(item_crc32);


	item->in_use = 0;
	item->next = NULL;

	return item;

EXIT:
	if (item)
	{
		delete_mad_item(item);
	}
	return NULL;
}

/*
 * need how many bytes
 */
static int mad_item_save_size(MAD_ITEM *mad_item)
{
	int size = 0;

	if (!mad_item)
	{
		return 0;
	}
	size += strlen(MAD_HEADER);
	size += MAD_ID_SIZE;
	size += sizeof(mad_item->type);
	size += sizeof(mad_item->extra_data_length);
	size += mad_item->extra_data_length;
	size += sizeof(mad_item->content.data_type);
	size += sizeof(mad_item->content.data_length);
	size += mad_item->content.data_length;
	size += sizeof(mad_item->content.crc32);
	size += sizeof(U32);

	return size;
}

static int boot_ad_data_max_size(void)
{
	MAD_ITEM *item;
	int size = 0;

	item = new_mad_item();
	if (item)
	{
		size = mad_interface_flash_size() - mad_item_save_size(item);
		delete_mad_item(item);
	}
	return size;
}

/*
 * return bytes number converted.
 * if error occurred, return 0
 */
static int mad_item_to_data_array(U8 *data, int space, MAD_ITEM *mad_item)
{
	int index = 0;
	U32 item_crc;

	if (!mad_item || mad_item_save_size(mad_item) > space)
	{
		return 0;
	}

	/* save m-ad item */
	memcpy(data + index, MAD_HEADER, strlen(MAD_HEADER));
	index += strlen(MAD_HEADER);
	memcpy(data + index, mad_item->id, MAD_ID_SIZE);
	index += MAD_ID_SIZE;
	memcpy(data + index, &(mad_item->type), sizeof(mad_item->type));
	index += sizeof(mad_item->type);
	memcpy(data + index, &(mad_item->extra_data_length), sizeof(mad_item->extra_data_length));
	index += sizeof(mad_item->extra_data_length);
	memcpy(data + index, mad_item->extra_data, mad_item->extra_data_length);
	index += mad_item->extra_data_length;

	/* save item content */
	memcpy(data + index, &(mad_item->content.data_type), sizeof(mad_item->content.data_type));
	index += sizeof(mad_item->content.data_type);
	memcpy(data + index, &(mad_item->content.data_length), sizeof(mad_item->content.data_length));
	index += sizeof(mad_item->content.data_length);
	memcpy(data + index, mad_item->content.data_addr, mad_item->content.data_length);
	index += mad_item->content.data_length;
	memcpy(data + index, &(mad_item->content.crc32), sizeof(mad_item->content.crc32));
	index += sizeof(mad_item->content.crc32);

	/* append item crc at tail */
	item_crc = mad_get_crc32(data, index);
	memcpy(data + index, &item_crc, sizeof(item_crc));
	index += sizeof(item_crc);

	if (index != mad_item_save_size(mad_item))
	{
		MAD_ERR("save size not match when save!");
	}
	return index;
}

/*
 * load boot ad from flash.
 * need call delete_mad_item after use!
 */
static MAD_ITEM *load_boot_ad_from_flash(void)
{
	U8 *flash = NULL;
	MAD_ITEM *mad_item = NULL;

	if (mad_interface_flash_size() <= 0)
	{
		return NULL;
	}
	if ((flash = SY_MALLOC(mad_interface_flash_size())) == NULL)
	{
		MAD_ERR("no enough memory when load boot ad from flash\n");
		return NULL;
	}
	if (!mad_interface_load_boot_ad(flash))
	{
		SY_FREE(flash);
		MAD_ERR("load ad data from flash fail!\n");
		return NULL;
	}
	mad_item = data_array_to_mad_item(flash, mad_interface_flash_size());
	if (mad_item)	/* it is a valid mad item */
	{
		MAD_INF("get mad item 0x%08x from flash!\n", mad_item);
		if (mad_item->type != MAD_TYPE_BOOT)
		{
			delete_mad_item(mad_item);
			mad_item = NULL;
		}
	}
	SY_FREE(flash);

	return mad_item;
}

/*
 * load boot ad to memory and add it into ad list.
 */
BOOL add_boot_ad_into_list(void)
{
	MAD_ITEM *mad_item = NULL;

	mad_item = load_boot_ad_from_flash();
	if (mad_item)
	{
		mad_list_add_item(mad_item);
	}

	return TRUE;
}

static BOOL save_boot_ad_into_flash(MAD_ITEM *boot_ad)
{
	U8 *flash;
	int total_len, len;

	total_len = mad_interface_flash_size();
	if (total_len <= 0)
	{
		return FALSE;
	}
	if ((flash = SY_MALLOC(total_len * 2)) == NULL)
	{
		return FALSE;
	}
	memset(flash, 0, mad_interface_flash_size());
	mad_interface_load_boot_ad(flash + total_len);
	len = mad_item_to_data_array(flash, total_len, boot_ad);
	if (len)
	{
		MAD_INF("boot ad len:%d\n", len);
		if (memcmp(flash, flash + total_len, total_len) != 0)
		{
			MAD_INF("ad data changed,need save!!\n");
			mad_interface_save_boot_ad(flash);
		}
	}
	SY_FREE(flash);

	return TRUE;
}

BOOL save_all_boot_ad_into_flash(void)
{
	MAD_ITEM *temp;
	BOOL result = TRUE;

	temp = get_mad_list_head();
	while ((temp = find_next_mad_item(temp)) != NULL)
	{
		if (mad_item_match_type(temp, MAD_TYPE_BOOT))
		{
			MAD_INF("find boot mad!\n");
			result = save_boot_ad_into_flash(temp);
			break;
		}
	}
	return result;
}


/***********************************************************************************
 *                                  show m-ad                                      *
 ***********************************************************************************/
void mad_show_ad_content(MAD_ITEM *ad)
{
	MAD_INF("show ad,data type is:%d\n", ad->content.data_type);

	switch (ad->content.data_type)
	{
		case MAD_DATA_TYPE_IFRAME:
			mad_interface_show_iframe_ad(ad->content.data_addr, ad->content.data_length, 5000);
			break;
		default:
			break;
	}
}

BOOL check_boot_logo_data(U8 *data, int len)
{
	unsigned char iframe_start_code[] = {0x00, 0x00, 0x01, 0xB3};
	int start_code_len = sizeof(iframe_start_code);

	if (len < start_code_len)
	{
		return FALSE;
	}
	if (memcmp(data, iframe_start_code, start_code_len) != 0)
	{
		return FALSE;
	}
	return TRUE;
}

static MAD_ITEM* convert_logo_data_to_boot_ad(U8 *data, int len)
{
	MAD_ITEM *boot_ad = NULL;

	boot_ad = new_mad_item();
	if (!boot_ad)
	{
		return NULL;
	}
	boot_ad->content.data_addr = SY_MALLOC(len);
	if (!boot_ad->content.data_addr)
	{
		delete_mad_item(boot_ad);
		return NULL;
	}
	boot_ad->type = MAD_TYPE_BOOT;
	boot_ad->content.data_type = MAD_DATA_TYPE_IFRAME;
	memcpy(boot_ad->content.data_addr, data, len);
	boot_ad->content.data_length = len;
	boot_ad->content.crc32 = mad_get_crc32(data, len);

	return boot_ad;
}

void mad_show_boot_ad(void)
{
	MAD_ITEM *boot_ad;
	U8 *logo_data;
	int logo_data_len;
	int max_len;

	boot_ad = load_boot_ad_from_flash();
	if (boot_ad)
	{
		mad_show_ad_content(boot_ad);
		delete_mad_item(boot_ad);
	}
	else if (!mad_interface_flash_use_boot_logo_zone())
	{
		MAD_INF("load boot ad item fail,show normal boot logo!\n");
		mad_interface_show_normal_boot_logo();
	}
	else
	{
		MAD_INF("load boot ad item fail,try to convert boot logo to boot ad!\n");
		max_len = boot_ad_data_max_size();
		logo_data = SY_MALLOC(max_len);
		if (!logo_data)
		{
			return;
		}
		logo_data_len = mad_interface_get_boot_logo_data(logo_data, max_len);
		if (logo_data_len > 0 && check_boot_logo_data(logo_data, logo_data_len))
		{
			boot_ad = convert_logo_data_to_boot_ad(logo_data, logo_data_len);
			if (boot_ad)
			{
				MAD_INF("convert boot logo to boot ad ok!\n");
				save_boot_ad_into_flash(boot_ad);
				mad_show_ad_content(boot_ad);
				delete_mad_item(boot_ad);
			}
		}
		SY_FREE(logo_data);
	}
}


/***********************************************************************************
 *                                     test                                        *
 ***********************************************************************************/
/*
 * test change boot ad
 * use radio logo as boot ad
 */
void mad_test_change_boot_ad(void)
{
	MAD_ITEM *error_boot_ad = NULL;
	U8 *flash = NULL;
	int total_len;
	int data_max_len;
	BOOL result = TRUE;

	MAD_INF("test change boot ad:\nuse test iframe data as boot ad,M-AD system must change to right ad after next startup.\n");
	total_len = mad_interface_flash_size();
	if (total_len <= sizeof(MAD_ITEM))
	{
		result = FALSE;
		goto EXIT;
	}
	if ((flash = SY_MALLOC(total_len)) == NULL)
	{
		MAD_ERR("no enough memory!!\n");
		result = FALSE;
		goto EXIT;
	}
	if ((error_boot_ad = new_mad_item()) == NULL)
	{
		result = FALSE;
		goto EXIT;
	}
	data_max_len = total_len - mad_item_save_size(error_boot_ad);

	if ((error_boot_ad->content.data_addr = SY_MALLOC(data_max_len)) == NULL)
	{
		MAD_ERR("no enough memory!!\n");
		result = FALSE;
		goto EXIT;
	}
	error_boot_ad->content.data_length = mad_interface_get_test_iframe_data(error_boot_ad->content.data_addr, data_max_len);
	if (error_boot_ad->content.data_length == 0)
	{
		MAD_ERR("logo test iframe data error!!\n");
		result = FALSE;
		goto EXIT;
	}
	error_boot_ad->type = MAD_TYPE_BOOT;
	error_boot_ad->content.data_type = MAD_DATA_TYPE_IFRAME;
	error_boot_ad->content.crc32 = mad_get_crc32(error_boot_ad->content.data_addr, error_boot_ad->content.data_length);

	memset(flash, 0, mad_interface_flash_size());
	if (mad_item_to_data_array(flash, total_len, error_boot_ad) > 0)
	{
		mad_interface_save_boot_ad(flash);
	}
	MAD_INF("save test logo data as boot ad OK.\n");

EXIT:
	if (flash)
	{
		SY_FREE(flash);
	}
	if (error_boot_ad)
	{
		delete_mad_item(error_boot_ad);
	}
	MAD_INF("change boot ad result %d.\n", result);
	//AutoDisBoxMessage(WAIT_FOR_1_SEC * 3, CENTER_JUST, PROMPT_MSG_X, PROMPT_MSG_Y, MSG_TYPE_INFO, 1,result ? "Change Boot Ad OK!" : "Change Boot Ad Fail!");
}

/*
 * test destroy boot ad
 * use mess data as boot ad data
 */
void mad_test_destroy_boot_ad(void)
{
	int total_len;
	U8 *flash = NULL;
	int i;
	BOOL result = TRUE;

	MAD_INF("test destroy boot ad:\nuse mess data as boot ad.\n");
	total_len = mad_interface_flash_size();
	if (total_len <= 0)
	{
		result = FALSE;
		goto EXIT;
	}
	if ((flash = SY_MALLOC(total_len)) == NULL)
	{
		result = FALSE;
		goto EXIT;
	}

	//gsSetRandomSeed(GSOS_TimeNow());
	for (i = 0; i < total_len; i++)
	{
		flash[i] = (U8)(RAND(0xFF) % 0x100);	//0~0xff
	}
	mad_interface_save_boot_ad(flash);

EXIT:
	if (flash)
	{
		SY_FREE(flash);
	}
	MAD_INF("destroy boot ad result %d.\n", result);
	//AutoDisBoxMessage(WAIT_FOR_1_SEC * 3, CENTER_JUST, PROMPT_MSG_X, PROMPT_MSG_Y, MSG_TYPE_INFO, 1,result ? "Destroy Boot Ad OK!" : "Destroy Boot Ad Fail!");
}

#endif	/* ENABLE_M_AD */
