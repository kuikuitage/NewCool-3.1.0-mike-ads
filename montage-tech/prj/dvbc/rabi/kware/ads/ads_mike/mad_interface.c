/*
 * mad_interface.c
 *
 *  Created on: 2015-4-8
 *      Author: Brant
 */

//#include "usifext.h"
//#include "gs_av_interface.h"

#if ENABLE_M_AD

#include "mad.h"
#include "mad_interface.h"
#include "mad_api.h"


char* mad_interface_dev_language(void)
{
	char *lang = NULL;

	switch (GetLanguage())
	{
		case ENGLISH_LANGUAGE:		lang = "English"; 	break;
		case GERMAN_LANGUAGE: 		lang = "German"; 	break;
		case RUSSIAN_LANGUAGE:		lang = "Russian";	break;
		case ARABIC_LANGUAGE:		lang = "Arabic";	break;
		case HUNGARIAN_LANGUAGE:	lang = "Hungarian";	break;
		case TURKISH_LANGUAGE:		lang = "Turkish";	break;
		case ITALIAN_LANGUAGE:		lang = "Italian";	break;
		case FRENCH_LANGUAGE:		lang = "French";	break;
		case SPANISH_LANGUAGE:		lang = "Spanish";	break;
		case FARSI_LANGUAGE:		lang = "Farsi";		break;
		case POLISH_LANGUAGE:		lang = "Polish";	break;
		case GREEK_LANGUAGE:		lang = "Greek";		break;
		case CZECH_LANGUAGE:		lang = "Czech";		break;
		case SLOVAK_LANGUAGE:		lang = "Slovak";	break;
		case UKRAINIAN_LANGUAGE:	lang = "Ukrainian";	break;
		case SWEDISH_LANGUAGE:		lang = "Swedish";	break;
		case DUTCH_LANGUAGE:		lang = "Dutch";		break;
		case THAI_LANGUAGE:			lang = "Thai";		break;
		case SLOVENIA_LANGUAGE:		lang = "Slovenia";	break;
		case BULGARIAN_LANGUAGE:	lang = "Bulgarian";	break;
		case ROMANIAN_LANGUAGE:		lang = "Romanian";	break;
		case PORTUGU_LANGUAGE:		lang = "Portugu";	break;
#if ENABLE_CHINESE_LANGUAGE
		case CHINESE_LANGUAGE:		lang = "Chinese";	break;
#endif
		case DANISH_LANGUAGE:		lang = "Danish";	break;
		case MONGOLIAN_LANGUAGE:	lang = "Mongolian";	break;
		case FINNISH_LANGUAGE:		lang = "Finnish";	break;
		case CROATIAN_LANGUAGE:		lang = "Croatian";	break;

		default:					lang = "unknown";	break;
	}
	return lang;
}

int mad_interface_dev_pid(void)
{
	return GetPlatformType();
}

int mad_interface_dev_cid(void)
{
	return get_customer_id();
}

int mad_interface_dev_mid(void)
{
	return get_model_id();
}

BOOL mad_interface_dev_sn(char *sn)
{
	GetDispSNNumber(sn);

	return TRUE;
}

BOOL mad_interface_dev_time(char *time)
{
	int minute;
	int hour;
	int date;
	int month;
	int year;

	GetRealDate(&year, &month, &date, &hour, &minute, FALSE);
	sprintf(time, "%04d-%02d-%02d %02d:%02d:00", year, month, date, hour, minute);

	return TRUE;
}

U32 mad_interface_memory_size(void)
{
	return 0x100000;	//1M
}

BOOL mad_interface_flash_use_boot_logo_zone(void)
{
#if (IS_ALI_M3503_SERIES || ALI_CHIPSET_TYPE == ALI_CHIPSET_3821) && defined(_8MB_FLASH_ENABLE_)
	return FALSE;
#endif
	return TRUE;
}

U32 mad_interface_flash_size(void)
{
	return flash_get_mad_size();
}

BOOL mad_interface_save_boot_ad(U8 *data)
{
	return flash_update_mad_data(data);
}

BOOL mad_interface_load_boot_ad(U8 *data)
{
	return flash_read_mad_data(data);
}

BOOL mad_interface_http_download(char *url, U8 **buffer, U32 *data_length)
{
	U8 *data;
	unsigned int length;
	int ret = FALSE;

	http_common_obtain_mutex();

	data = http_download_file(url, &length, NULL, E_HTTP_COMMON_GET);
	if (length > 0)
	{
		*buffer = GSOS_Malloc(length);
		if (*buffer)
		{
			memcpy(*buffer, data + sizeof(U32), length);
			*data_length = length;
			ret = TRUE;
		}
	}
	http_free_download_buffer();
	http_common_release_mutex();

	return ret;
}

char* mad_interface_base64_encode_string(char *src, U32 src_length)
{
	char *dst_string = NULL;

	dst_string = GSOS_Malloc(src_length * 2);
	if (dst_string)
	{
		base64_encode(dst_string, src, src_length);
	}

	return dst_string;
}

char* mad_interface_base64_decode_string(char *src, U32 src_length)
{
	char *src_string;
	char *dst_string = NULL;

	if (src[src_length - 1] == '\0')
	{
		src_string = src;
	}
	else
	{
		src_string = GSOS_Malloc(src_length + 1);
		if (src_string)
		{
			memset(src_string, 0, src_length + 1);
			memcpy(src_string, src, src_length);
		}
	}
	if (src_string)
	{
		dst_string = GSOS_Malloc(src_length);
		if (dst_string)
		{
			base64_decode(dst_string, src_string);
		}
		if (src_string != src)
		{
			GSOS_Free(src_string);
		}
	}

	return dst_string;
}


void mad_interface_show_iframe_ad(U8 *iframe_data, int data_length, int show_time_ms)
{
	gsShowIFrame(iframe_data, data_length, TRUE);
	GSOS_TaskDelay(show_time_ms);
}

void mad_interface_show_normal_boot_logo(void)
{
	PlayMPEG2(START_LOGO, FALSE);
	GSOS_TaskDelay(3000);
}

static int get_system_logo_data(unsigned int logo_addr, U8 *data, int max_length)
{
	unsigned int logo_size_len = 4;
	unsigned int logo_size_temp = 0;
	unsigned int logo_size_real = 0;
	unsigned int logo_size_ret = 0;		/* just for return */
	unsigned char *logo_buf = NULL;
	unsigned char *temp_buf = NULL;
	unsigned char iframe_start_code[] = {0x00, 0x00, 0x01, 0xB3};

	if (!FlashReadArray(logo_addr, logo_size_len, (U8*)&logo_size_temp))
	{
		goto EXIT;
	}
	gs_decrypt_flash_data(&logo_size_temp, &logo_size_real, logo_size_len);
	if (logo_size_real > 49000)
	{
		goto EXIT;
	}
	logo_buf = GSOS_Malloc(logo_size_real + logo_size_len);
	temp_buf = GSOS_Malloc(logo_size_real + logo_size_len);
	if (logo_buf == NULL || temp_buf == NULL)
	{
		goto EXIT;
	}
	FlashReadArray(logo_addr, logo_size_real + logo_size_len, temp_buf);
	gs_decrypt_flash_data(temp_buf, logo_buf, logo_size_real + logo_size_len);	//read all the logo.bin,include size header.
	if (memcmp(iframe_start_code, logo_buf + logo_size_len, sizeof(iframe_start_code)) != 0) //somtimes logo data is wrong and make box blocking here 2011.07.28
	{
		goto EXIT;
	}
	if (logo_size_real > max_length)
	{
		goto EXIT;
	}
	memcpy(data, logo_buf + logo_size_len, logo_size_real);
	logo_size_ret = logo_size_real;

EXIT:
	if (logo_buf != NULL)
	{
		GSOS_Free(logo_buf);
	}
	if (temp_buf != NULL)
	{
		GSOS_Free(temp_buf);
	}
	return logo_size_ret;
}

int mad_interface_get_boot_logo_data(U8 *data, int max_length)
{
	return get_system_logo_data(FLASH_LOGO_ADDR, data, max_length);
}

int mad_interface_get_test_iframe_data(U8 *data, int max_length)
{
	return get_system_logo_data(FLASH_LOGO_ADDR + FLASH_LOGO_SIZE, data, max_length);	/* radio logo */
}

#endif	/* ENABLE_M_AD */
