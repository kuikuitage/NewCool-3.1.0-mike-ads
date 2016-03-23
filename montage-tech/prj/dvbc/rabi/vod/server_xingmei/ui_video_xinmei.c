/******************************************************************************/
/******************************************************************************/
/*!
 Include files
 */
#include "ui_common.h"
#include "commonData.h"
#if ENABLE_FILE_PLAY
#include "file_play_api.h"
//#include "ui_onmov_provider.h"
#include "xingmeiDataProvider.h"
#include "ui_video_xinmei.h"
#include "ui_mute.h"
#include "lib_char.h"
#include "sys_status.h"
#include "common_filter.h"
#include "ui_small_list_v2.h"
#include "ui_epg_api.h"
#include "ui_volume.h"
#include "ui_iptv_api.h"
#include "ui_iptv_prot.h"

#include "sys_dbg.h"
#include "xmTV.h"
#include "xingmeiDataPorcess.h"


#define printf_ret(ret)   if(SUCCESS != ret)\
                          {\
                              UI_VIDEO_PRINF("[%s]: ret = %d in %d line\n", \
                                                __FUNCTION__, ret, __LINE__);\
                          }


static BOOL xm_video_get_if_ad();
/*!
 * Get current play time
 */
static u32 xm_video_get_play_time(void)
{
	return ui_video_c_get_play_time();
}

/*!
 * Get current play state
 */
static int xm_video_get_play_state(void)
{
	return ui_video_c_get_play_state();
}

/*!
 * Get total time of video
 */
static u32 xm_video_get_total_time_by_sec(void)
{
	DEBUG(XM_PLAY, INFO, "\n");
	return ui_video_c_get_total_time_by_sec();
}

/*!
 * Get total ad time of video
 */
static u32 xm_video_get_total_ad_time_by_sec(void)
{
	DEBUG(XM_PLAY, INFO, "\n");
	return 0;
}

/*!
 * Get resolution of video
 */
static void xm_video_get_resolution(rect_size_t *p_rect)
{
	return ui_video_c_get_resolution(p_rect);
}

/*!
 * Get vd of video
 */
static int xm_video_get_current_format(void)
{
	DEBUG(XM_PLAY, INFO, "\n");
	return 0;
}

static int xm_video_seek(s32 time_sec)
{
	return ui_video_c_seek(time_sec);
}

/*!
 * Pause or resume playing
 */
static int xm_video_pause_resume(void)
{
	return ui_video_c_pause_resume();
}

void xm_video_set_usr_stop_flag(BOOL flag)
{
	return ui_video_c_set_usr_stop_flag(flag);
}

/*!
 * Stop playing
 */
static int xm_video_stop(void)
{
	return ui_video_c_stop();
}

static int xm_video_play_by_url_ex(video_url_info_t *pp_url_list, 
												u32 url_cnt,
												u32 seek_play_time,
												int vd)
{
	u8 **list;
	int i;
	list =  (u8 ** )SY_CALLOC(1, sizeof(u8 *) * 256);
	if (list == NULL)
		return -1;
	for (i=0;i<url_cnt && 256;i++)
	{
		list[i] = pp_url_list[i].playUrl;
	}
	return ui_video_c_play_by_url_ex(list, url_cnt, seek_play_time, OTT_VOD_MODE);
}

/*iqy need*/
static int xm_video_play_by_url(video_url_info_t *p_net_url, u32 seek_play_time,int vd)
{
	return ui_video_c_play_by_url(p_net_url->playUrl , seek_play_time,OTT_VOD_MODE);
}

static BOOL xm_video_get_usr_stop_flag(void)
{
	return ui_video_c_get_usr_stop_flag();
}

static BOOL xm_video_init_state(void)
{
	return ui_video_c_init_state();
}

/*!
 * Destroy file play module
 */
static int xm_video_destroy(void)
{
	return ui_video_c_destroy();
}
/*!
 * Create file play module
 */
static int xm_video_create(u8 play_func)
{
	return  ui_video_c_create(play_func);
}

static BOOL xm_video_get_if_ad()
{
	return 0;
}

static VodPlayerInterface_t iqyPlayerInterface;
const VodPlayerInterface_t* GetXingMeiPlayerInterface(void)
{
	(void)xm_video_get_usr_stop_flag;
	(void)xm_video_init_state;
	if (!iqyPlayerInterface.create)
	{
		iqyPlayerInterface.create 		= xm_video_create;
		iqyPlayerInterface.destory 		= xm_video_destroy;
		iqyPlayerInterface.getCurrentFormat = xm_video_get_current_format;
		iqyPlayerInterface.getCurrentPlayTime = xm_video_get_play_time;
		iqyPlayerInterface.getPlayState 	= xm_video_get_play_state;
		iqyPlayerInterface.getResolution	= xm_video_get_resolution;
		iqyPlayerInterface.getTotalAdTime = xm_video_get_total_ad_time_by_sec;
		iqyPlayerInterface.getTotalTimeBySec = xm_video_get_total_time_by_sec;
		iqyPlayerInterface.ifPlayingAd   	= xm_video_get_if_ad;
		iqyPlayerInterface.pause_resume	 = xm_video_pause_resume;
		iqyPlayerInterface.playUrl 		= xm_video_play_by_url;
		iqyPlayerInterface.playUrlEx		= xm_video_play_by_url_ex;
		iqyPlayerInterface.seek		= xm_video_seek;
		iqyPlayerInterface.videoStop	= xm_video_stop;
	}
	return &iqyPlayerInterface;
}

#endif

