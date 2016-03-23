/******************************************************************************/

/******************************************************************************/
#ifndef __MEM_CFG_H__
#define __MEM_CFG_H__


//warriors

typedef enum
{
  MEMCFG_T_NORMAL,
}mem_cfg_t;

/*! Video buffer classification.*/
typedef enum
{
  BLOCK_AV_BUFFER = 0,
  BLOCK_REC_BUFFER,
  BLOCK_PLAY_BUFFER,
  BLOCK_EPG_BUFFER,
  BLOCK_UI_RESOURCE_BUFFER,
  BLOCK_OSD_VSURF_BUFFER,
  BLOCK_GUI_ANIM_BUFFER,

  BLOCK_MAX_ID,
} block_id_t;

#define STATIC_BLOCK_NUM    BLOCK_MAX_ID


/*!
   Memory configuration
  */
#define SYS_MEMORY_END  0x8000000//128M

#define AV_BUFFER_SIZE  VIDEO_FW_CFG_SIZE//(SYS_MEMORY_END - AV_BUFFER_ADDR)
#define AV_BUFFER_ADDR  (VIDEO_FW_CFG_ADDR & 0x0FFFFFFF) //(SYSTEM_MEMORY_END & 0x0FFFFFFF)

//#define SUB_BUFFER_SIZE (1810 * 2 * KBYTES)//1280*(720 + 4)*4
//#define SUB_BUFFER_ADDR (((SYSTEM_MEMORY_END & 0x0FFFFFFF) - SUB_BUFFER_SIZE)  | 0xa0000000)

//#define SUB_VSCALER_BUFFER_SIZE (1810 * 2 * KBYTES)
//#define SUB_VSCALER_BUFFER_ADDR ((SUB_BUFFER_ADDR - SUB_VSCALER_BUFFER_SIZE)  | 0xa0000000)


#define SUB_BUFFER_SIZE (900 * 2 * KBYTES)

#define SUB_BUFFER_ADDR (((SYSTEM_MEMORY_END & 0x0FFFFFFF) - SUB_BUFFER_SIZE)  | 0xa0000000)

#define SUB_VSCALER_BUFFER_SIZE (900 * 2 * KBYTES)
#define SUB_VSCALER_BUFFER_ADDR ((SUB_BUFFER_ADDR - SUB_VSCALER_BUFFER_SIZE)  | 0xa0000000)



#define OSD1_BUFFER_SIZE (1810 * 2 * KBYTES)
#define OSD1_BUFFER_ADDR ((SUB_VSCALER_BUFFER_ADDR - OSD1_BUFFER_SIZE)  | 0xa0000000)

#define OSD1_VSCALER_BUFFER_SIZE (1810 * 2 * KBYTES)
#define OSD1_VSCALER_BUFFER_ADDR ((OSD1_BUFFER_ADDR - OSD1_VSCALER_BUFFER_SIZE)  | 0xa0000000)

#define OSD0_BUFFER_SIZE (0 * KBYTES)//(960*600*4)
#define OSD0_BUFFER_ADDR ((OSD1_VSCALER_BUFFER_ADDR - OSD0_BUFFER_SIZE)  | 0xa0000000)

#define OSD0_VSCALER_BUFFER_SIZE 0 //1280*1080*2,����4K����
#define OSD0_VSCALER_BUFFER_ADDR ((OSD0_BUFFER_ADDR - OSD0_VSCALER_BUFFER_SIZE)  | 0xa0000000)


#define OSD_VSURF_BUFFER_SIZE  0
#define OSD_VSURF_BUFFER_ADDR ((OSD0_VSCALER_BUFFER_ADDR - OSD_VSURF_BUFFER_SIZE) & (~0xa0000000))

#define GUI_ANIM_BUFFER_SIZE (0 * KBYTES)
#define GUI_ANIM_BUFFER_ADDR (OSD_VSURF_BUFFER_ADDR - GUI_ANIM_BUFFER_SIZE)

#define DES_BUFFER_SIZE (0 * KBYTES) //0.5M  //if you need modify it. tell andy.chen please
#define DES_BUFFER_ADDR (GUI_ANIM_BUFFER_ADDR - DES_BUFFER_SIZE)

#define PLAY_BUFFER_SIZE (100 * KBYTES) // 512K BYTES //dmx limit 256K (112K use by fast revend trick mode)
#define PLAY_BUFFER_ADDR (DES_BUFFER_ADDR - PLAY_BUFFER_SIZE)

//#define EPG_BUFFER_SIZE   (1024 * KBYTES)//(1 * MBYTES + 512 * KBYTES)
//#define EPG_BUFFER_ADDR   (PLAY_BUFFER_ADDR - EPG_BUFFER_SIZE)

//#define GUI_RESOURCE_BUFFER_SIZE (20 * MBYTES)//(4 * MBYTES + 512 * KBYTES)
#define GUI_RESOURCE_BUFFER_SIZE (5 * MBYTES)//(21 * MBYTES)//(4 * MBYTES + 512 * KBYTES)
//#define GUI_RESOURCE_BUFFER_ADDR (EPG_BUFFER_ADDR - GUI_RESOURCE_BUFFER_SIZE)
#define GUI_RESOURCE_BUFFER_ADDR (PLAY_BUFFER_ADDR - GUI_RESOURCE_BUFFER_SIZE)




#define GUI_PARTITION_SIZE   (512 * KBYTES)//add 3.53M for mainmenu logo

#if		defined ADS_DIVI_SUPPORT
#define SYS_PARTITION_SIZE        (0x2000000 - 0x200000 - 4500*KBYTES)
#elif	defined TR_CA || defined (TEMP_SUPPORT_DS_AD) || defined (ADS_DESAI_SUPPORT) || defined (SUPPORT_DVB_AD) || defined SUPPORT_EXTERN_IPTV
#define SYS_PARTITION_SIZE        (0x2000000 - 0x200000 - 3000*KBYTES)
#else
#define SYS_PARTITION_SIZE        (0x2000000 - 0x200000 - 1700*KBYTES)
#endif
#define SYS_PARTITION_ATOM        64

/*!
  multiplex size
  */
#define MUSIC_MODULE_USED_SIZE (4 * MBYTES)  

#define MUSIC_REGION_USED_SIZE (8 * MBYTES)

#define PICTURE_MODULE_USED_SIZE (16 * MBYTES)

#define PICTURE_REGION_USED_SIZE (8 * MBYTES)

#define TS_PLAY_BUFFER_LEN  (490 * 188) //to ts sequence


/*!
  Set memory config mode
  \param[in] cfg parameter for memory confi
  */
void mem_cfg(mem_cfg_t cfg);
#endif

