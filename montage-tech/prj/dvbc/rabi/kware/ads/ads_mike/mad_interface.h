/*
 * mad_interface.h
 *
 *  Created on: 2015-4-8
 *      Author: Brant
 */

#ifndef _M_AD_INTERFACE_H_
#define _M_AD_INTERFACE_H_

/*
 * language of current device using
 */
char* mad_interface_dev_language(void);

/*
 * platform id of current device
 */
int mad_interface_dev_pid(void);

/*
 * customer id of current device
 */
int mad_interface_dev_cid(void);

/*
 * model id of current device
 */
int mad_interface_dev_mid(void);

/*
 * serial number of current device
 */
BOOL mad_interface_dev_sn(char *sn);

/*
 * system time,use format:YYYY-MM-DD hh:mm:ss
 */
BOOL mad_interface_dev_time(char *time);

/*
 * memory size for m-ad system,return bytes number
 */
U32 mad_interface_memory_size(void);

/*
 * m-ad system use same zone with boot logo or not.
 * P.S. if no enough flash space,you can save boot ad to boot logo zone
 */
BOOL mad_interface_flash_use_boot_logo_zone(void);

/*
 * flash size for m-ad system,return bytes number
 */
U32 mad_interface_flash_size(void);

/*
 * save ad data into flash,data length is mad_interface_flash_size()
 */
BOOL mad_interface_save_boot_ad(U8 *data);

/*
 * load ad data from flash,data length is mad_interface_flash_size()
 */
BOOL mad_interface_load_boot_ad(U8 *data);

/*
 * download data from network in http protocol.
 */
BOOL mad_interface_http_download(char *url, U8 **buffer, U32 *data_length);

/*
 * base64 encode.
 * return base64 encode string end with '\0', need FREE it after use.
 */
char* mad_interface_base64_encode_string(char *src, U32 src_length);

/*
 * base64 decode
 * return base64 decode string end with '\0', need FREE it after use.
 */
char* mad_interface_base64_decode_string(char *src, U32 src_length);

/*
 * show I frame picture
 * show_time_ms : show I frame time in ms.
 */
void mad_interface_show_iframe_ad(U8 *iframe_data, int data_length, int show_time_ms);

/*
 * show normal boot logo.
 * when "load boot ad from flash fail" && "boot ad NOT use same zone with boot logo", will call this function
 */
void mad_interface_show_normal_boot_logo(void);

/*
 * get boot logo iframe data.
 * return actual data size,return 0 if error occurred
 */
int mad_interface_get_boot_logo_data(U8 *data, int max_length);

/*
 * get a i-frame data for test(recommend use radio logo data)
 * return actual data size,return 0 if error occurred
 */
int mad_interface_get_test_iframe_data(U8 *data, int max_length);

#endif /* _M_AD_INTERFACE_H_ */
