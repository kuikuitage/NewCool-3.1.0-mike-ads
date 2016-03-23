/*
 * mad.h
 *
 *  Created on: 2015-4-2
 *      Author: Brant
 */

#ifndef _M_AD_H_
#define _M_AD_H_


/***********************************************************************************
 *                                   log level                                     *
 ***********************************************************************************/
#define MAD_DEBUG_INFO		1
#define MAD_DEBUG_WARNING	2
#define MAD_DEBUG_ERROR		3
#define MAD_DEBUG_NONE		4
#define MAD_DEBUG_LEVEL		MAD_DEBUG_INFO

#define ENABLE_DEBUG_INF	(MAD_DEBUG_LEVEL<=MAD_DEBUG_INFO)
#define ENABLE_DEBUG_WRN	(MAD_DEBUG_LEVEL<=MAD_DEBUG_WARNING)
#define ENABLE_DEBUG_ERR	(MAD_DEBUG_LEVEL<=MAD_DEBUG_ERROR)
#define ENABLE_DEBUG_MAD	(ENABLE_DEBUG_INF||ENABLE_DEBUG_WRN||ENABLE_DEBUG_ERR)

#if ENABLE_DEBUG_INF
#define MAD_INF(fmt, args...)		printf("MAD INF: "fmt, ##args)
#else
#define MAD_INF(fmt, args...)
#endif

#if ENABLE_DEBUG_WRN
#define MAD_WRN(fmt, args...)		printf("MAD WRN: "fmt, ##args)
#else
#define MAD_WRN(fmt, args...)
#endif

#if ENABLE_DEBUG_ERR
#define MAD_ERR(fmt, args...)		printf("MAD ERR: "fmt, ##args)
#else
#define MAD_ERR(fmt, args...)
#endif


/***********************************************************************************
 *                                   constant                                      *
 ***********************************************************************************/
#define MAD_SYS_VERSION		(1)

#define MAD_ID_SIZE			16
#define MAD_VERSION_SIZE	32


/***********************************************************************************
 *                                    typedef                                      *
 ***********************************************************************************/
typedef enum
{
	MAD_TYPE_BOOT = 1,	/* show ad when stb bootup */
	MAD_TYPE_APP,		/* show ad when user waiting stb do something */
	MAD_TYPE_SUBTITLE,	/* show ad as a subtitle */
	MAD_TYPE_CORNER,	/* show ad at the corner of screen */
	MAD_TYPE_NUM
} MAD_TYPE;

typedef enum
{
	MAD_DATA_TYPE_TEXT,
	MAD_DATA_TYPE_BMP,
	MAD_DATA_TYPE_JPG,
	MAD_DATA_TYPE_IFRAME,
	MAD_DATA_TYPE_VIDEO,
	MAD_DATA_TYPE_NUM
} MAD_DATA_TYPE;


typedef struct _mad_data_
{
	U32		data_type;
	U32		data_length;
	U8*		data_addr;
	U32		crc32;
} MAD_DATA;


typedef struct _mad_item_
{
/*	S8			header[4]; */			/* always "M-AD". save to flash, but not in memory */
	S8			id[MAD_ID_SIZE];
	U16			type;					/* refer to MAD_TYPE */
	U16			extra_data_length;
	void*		extra_data;

	MAD_DATA 	content;

	U32			in_use:1;				/* memory variable,not save to flash */

	struct _mad_item_ *next;			/* memory variable,not save to flash */
/*	U32			item_crc32; */			/* save to flash, but not in memory */
} MAD_ITEM;



/***********************************************************************************
 *                                   interface                                     *
 ***********************************************************************************/
BOOL mad_set_content_version(int type, U32 version);
U32 mad_get_content_version(int type);
BOOL is_same_with_current_version(int type, U32 version);

cJSON* parse_mad_json_data(char *data, int len);
BOOL get_json_item_num_value(double *value, cJSON *obj, const char *string);
BOOL get_json_item_string_value(char **value, cJSON *obj, const char *string);


MAD_ITEM* new_mad_item_if_not_exsit(char *id);
BOOL set_mad_item_data(MAD_ITEM *item, int data_type, U8 *data, int length);

void reset_all_mad_item_in_use_flag(void);
void delete_all_unused_mad_item(void);

BOOL add_boot_ad_into_list(void);
BOOL save_all_boot_ad_into_flash(void);
void delete_boot_ad_from_memory(void);


void mad_show_boot_ad(void);

/* for test */
void mad_test_change_boot_ad(void);
void mad_test_destroy_boot_ad(void);

#endif /* _M_AD_H_ */
