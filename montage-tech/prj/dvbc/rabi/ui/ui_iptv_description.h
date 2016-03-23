/****************************************************************************

****************************************************************************/
#ifndef __UI_IPTV_DESCRIPTION_H__
#define __UI_IPTV_DESCRIPTION_H__

//right cont
#define IPTV_DESC_DESC_TOP 69

#define IPTV_DESC_DESC_CONTX  (405)
#define IPTV_DESC_DESC_CONTY  (IPTV_DESC_DESC_TOP)//90
#define IPTV_DESC_DESC_CONTW (785)
#define IPTV_DESC_DESC_CONTH  (55)

//right title
#define IPTV_DESC_RIGHT_TITLEX 20
#define IPTV_DESC_RIGHT_TITLEY 10
#define IPTV_DESC_RIGHT_TITLEW 560
#define IPTV_DESC_RIGHT_TITLEH 40

//score
#define IPTV_DESC_RIGHT_SCOREX 630
#define IPTV_DESC_RIGHT_SCOREY 10
#define IPTV_DESC_RIGHT_SCOREW 80
#define IPTV_DESC_RIGHT_SCOREH 40

//score txt
#define IPTV_DESC_RIGHT_TXT_SCOREX 710
#define IPTV_DESC_RIGHT_TXT_SCOREY 10
#define IPTV_DESC_RIGHT_TXT_SCOREW 50
#define IPTV_DESC_RIGHT_TXT_SCOREH 40

//picture
#define IPTV_DESC_PICTUREX   (90)
#define IPTV_DESC_PICTUREY   (IPTV_DESC_DESC_TOP)
#define IPTV_DESC_PICTUREW  (286)
#define IPTV_DESC_PICTUREH   (396)

//desc cont
#define IPTV_DESC_CNTX  (405)
#define IPTV_DESC_CNTY  (IPTV_DESC_DESC_CONTY + IPTV_DESC_DESC_CONTH + 10)
#define IPTV_DESC_CNTW (785)
#define IPTV_DESC_CNTH  (331)

#define IPTV_DESC_TEXT_INTERVAL  0
#define IPTV_DESC_TEXT_VERTICAL  0
#define IPTV_DESC_VARIETY_CNTH 540


//vdo year 
#define IPTV_DESC_TEXT_VDO_YEAR_X  (10)
#define IPTV_DESC_TEXT_VDO_YEAR_Y  (10)
#define IPTV_DESC_TEXT_VDO_YEAR_W  60
#define IPTV_DESC_TEXT_VDO_YEAR_H  30

//vdo txt year
#define IPTV_DESC_VDO_TXT_YEAR_X  (IPTV_DESC_TEXT_VDO_YEAR_X + IPTV_DESC_TEXT_VDO_YEAR_W + 20)
#define IPTV_DESC_VDO_TXT_YEAR_Y  (IPTV_DESC_TEXT_VDO_YEAR_Y)
#define IPTV_DESC_VDO_TXT_YEAR_W  (340 - IPTV_DESC_VDO_TXT_YEAR_X)
#define IPTV_DESC_VDO_TXT_YEAR_H  30


// vdo series
#define IPTV_DESC_TEXT_VDO_SERIES_X  (IPTV_DESC_VDO_TXT_YEAR_X + IPTV_DESC_VDO_TXT_YEAR_W)
#define IPTV_DESC_TEXT_VDO_SERIES_Y  10
#define IPTV_DESC_TEXT_VDO_SERIES_W  (100)
#define IPTV_DESC_TEXT_VDO_SERIES_H  30

// vdo txt series
#define IPTV_DESC_VDO_TXT_SERIES_X  (30 + IPTV_DESC_TEXT_VDO_SERIES_X + IPTV_DESC_TEXT_VDO_SERIES_W + IPTV_DESC_TEXT_INTERVAL)
#define IPTV_DESC_VDO_TXT_SERIES_Y  10
#define IPTV_DESC_VDO_TXT_SERIES_W (730 - IPTV_DESC_VDO_TXT_SERIES_X )
#define IPTV_DESC_VDO_TXT_SERIES_H  30

//vdo attr
#define IPTV_DESC_TEXT_VDO_ATTR_X  10
#define IPTV_DESC_TEXT_VDO_ATTR_Y  (10 + IPTV_DESC_TEXT_VDO_SERIES_H +  IPTV_DESC_TEXT_VERTICAL)
#define IPTV_DESC_TEXT_VDO_ATTR_W  60
#define IPTV_DESC_TEXT_VDO_ATTR_H  30

//vdo txt attr
#define IPTV_DESC_VDO_TXT_ATTR_X  (IPTV_DESC_TEXT_VDO_ATTR_X + IPTV_DESC_TEXT_VDO_ATTR_W + 20)
#define IPTV_DESC_VDO_TXT_ATTR_Y  (IPTV_DESC_TEXT_VDO_ATTR_Y)
#define IPTV_DESC_VDO_TXT_ATTR_W (730 - IPTV_DESC_VDO_TXT_ATTR_X)
#define IPTV_DESC_VDO_TXT_ATTR_H  30

//vdo directer
#define IPTV_DESC_TEXT_VDO_DIRECTER_X  10
#define IPTV_DESC_TEXT_VDO_DIRECTER_Y  (10 + IPTV_DESC_TEXT_VDO_SERIES_H +  IPTV_DESC_TEXT_VERTICAL)
#define IPTV_DESC_TEXT_VDO_DIRECTER_W  60
#define IPTV_DESC_TEXT_VDO_DIRECTER_H  30

//vdo txt directer
#define IPTV_DESC_VDO_TXT_DIRECTER_X  (IPTV_DESC_TEXT_VDO_DIRECTER_X + IPTV_DESC_TEXT_VDO_DIRECTER_W + 20)
#define IPTV_DESC_VDO_TXT_DIRECTER_Y  (IPTV_DESC_TEXT_VDO_DIRECTER_Y)
#define IPTV_DESC_VDO_TXT_DIRECTER_W (380 - IPTV_DESC_VDO_TXT_DIRECTER_X)
#define IPTV_DESC_VDO_TXT_DIRECTER_H  30

// vdo actor
#define IPTV_DESC_TEXT_VDO_ACTOR_X  (380)
#define IPTV_DESC_TEXT_VDO_ACTOR_Y  (10 + IPTV_DESC_TEXT_VDO_SERIES_H +  IPTV_DESC_TEXT_VERTICAL)
#define IPTV_DESC_TEXT_VDO_ACTOR_W  60
#define IPTV_DESC_TEXT_VDO_ACTOR_H  30

// vdo txt actor
#define IPTV_DESC_VDO_TXT_ACTOR_X  (30 + IPTV_DESC_TEXT_VDO_ACTOR_X + IPTV_DESC_TEXT_VDO_ACTOR_W + IPTV_DESC_TEXT_INTERVAL)
#define IPTV_DESC_VDO_TXT_ACTOR_Y  (10 +  IPTV_DESC_TEXT_VDO_SERIES_H +  IPTV_DESC_TEXT_VERTICAL)
#define IPTV_DESC_VDO_TXT_ACTOR_W  (730 - IPTV_DESC_VDO_TXT_ACTOR_X )
#define IPTV_DESC_VDO_TXT_ACTOR_H  30




//description text title
#define IPTV_DESC_TEXT_TITLE_X  10
#define IPTV_DESC_TEXT_TITLE_Y  (IPTV_DESC_TEXT_VDO_ACTOR_Y + IPTV_DESC_TEXT_VDO_ACTOR_H)
#define IPTV_DESC_TEXT_TITLE_W  60
#define IPTV_DESC_TEXT_TITLE_H  30

//description text
#define IPTV_DESC_TEXT_X  (IPTV_DESC_TEXT_TITLE_X + IPTV_DESC_TEXT_TITLE_W + 20)
#define IPTV_DESC_TEXT_Y  IPTV_DESC_TEXT_TITLE_Y
#define IPTV_DESC_TEXT_W  (765 - IPTV_DESC_TEXT_X)
#define IPTV_DESC_TEXT_H  100

//vodeo rsc mbox
#define  IPTV_VIDEO_RSC_MBOX_X  90
#define  IPTV_VIDEO_RSC_MBOX_Y  (IPTV_DESC_TEXT_Y + IPTV_DESC_TEXT_H + 10)
#define  IPTV_VIDEO_RSC_MBOX_W  280
#define  IPTV_VIDEO_RSC_MBOX_H  COMM_CTRL_H//36

#define IPTV_VIDEO_RSC_ITEM 3
#define IPTV_VIDEO_RSC_COL 3

#define IPTV_VIDEO_RSC_ROW  1

//series number mbox
#define  IPTV_SERIES_NUM_MBOX_X 50
#define  IPTV_SERIES_NUM_MBOX_Y  IPTV_VIDEO_RSC_MBOX_Y + IPTV_VIDEO_RSC_MBOX_H + 10
#define  IPTV_SERIES_NUM_MBOX_W IPTV_DESC_CNTW - 2*IPTV_SERIES_NUM_MBOX_X
#define  IPTV_SERIES_NUM_MBOX_H  30

#define IPTV_SERIES_NUM_WINCOL 5
#define IPTV_SERIES_NUM_WINROW  1
#define IPTV_SERIES_NUM_ROW  1
#define IPTV_SERIES_NUM_PER_PAGE_ITEMS 10 
//on command tv series mbox
#define  IPTV_DESC_MBOX_X 40
#define  IPTV_DESC_MBOX_Y  IPTV_SERIES_NUM_MBOX_Y + IPTV_SERIES_NUM_MBOX_H + 10
#define  IPTV_DESC_MBOX_W IPTV_DESC_CNTW - 2*IPTV_DESC_MBOX_X
#define  IPTV_DESC_MBOX_H  30

#define IPTV_DESC_COL 10
#define IPTV_DESC_ROW  1
#define IPTV_DESC_WINCOL 10
#define IPTV_DESC_WINROW  1

//recommend information mbox
#define  IPTV_DESC_RECOMM_INFO_MBOX_X  90
#define  IPTV_DESC_RECOMM_INFO_MBOX_Y  480
#define  IPTV_DESC_RECOMM_INFO_MBOX_W 1165 - 65
#define  IPTV_DESC_RECOMM_INFO_MBOX_H  210

#define IPTV_DESC_RECOMM_INFO_NUM  8

#define  IPTV_RECOMM_ITEM_X 25
#define  IPTV_RECOMM_ITEM_Y 10
#define  IPTV_RECOMM_ITEM_W 118
#define  IPTV_RECOMM_ITEM_H 190


//#define IPTV_RECOMM_ITEM_VGAP 20
#define IPTV_RECOMM_ITEM_HGAP 10

#define  IPTV_RECOMMPIC_X 0
#define  IPTV_RECOMMPIC_Y 2
#define  IPTV_RECOMMPIC_W (IPTV_RECOMM_ITEM_W)
#define  IPTV_RECOMMPIC_H 146

#define  IPTV_RECOMMNANE_X (IPTV_RECOMPIC_BMP_OFFSET)
#define  IPTV_RECOMMNAME_Y 148
#define  IPTV_RECOMMNAME_W (IPTV_RECOMM_ITEM_W - 2*IPTV_RECOMPIC_BMP_OFFSET)
#define  IPTV_RECOMMNAME_H 40

#define  IPTV_RECOMPIC_OFFSET 5
#define  IPTV_RECOMPIC_BMP_OFFSET 3
#define  IPTV_RECOMMNAME_OFFSET 5
#define  IPTV_RECOMM_ITEM_VGAP 15

//movie play descriptions
//movie year 
#define IPTV_DESC_TEXT_MOVIE_YEAR_X  (10)
#define IPTV_DESC_TEXT_MOVIE_YEAR_Y  (10)
#define IPTV_DESC_TEXT_MOVIE_YEAR_W  (60)
#define IPTV_DESC_TEXT_MOVIE_YEAR_H  (30)

//movie txt year
#define IPTV_DESC_MOVIE_TXT_YEAR_X  (IPTV_DESC_TEXT_MOVIE_YEAR_X + IPTV_DESC_TEXT_MOVIE_YEAR_W + 20)
#define IPTV_DESC_MOVIE_TXT_YEAR_Y  (IPTV_DESC_TEXT_MOVIE_YEAR_Y)
#define IPTV_DESC_MOVIE_TXT_YEAR_W (380 - IPTV_DESC_MOVIE_TXT_YEAR_X)
#define IPTV_DESC_MOVIE_TXT_YEAR_H  (IPTV_DESC_TEXT_MOVIE_YEAR_H)


// movie duration
#define IPTV_DESC_TEXT_MOVIE_DURATION_X  (IPTV_DESC_MOVIE_TXT_YEAR_X + IPTV_DESC_MOVIE_TXT_YEAR_W)
#define IPTV_DESC_TEXT_MOVIE_DURATION_Y  (IPTV_DESC_TEXT_MOVIE_YEAR_Y)
#define IPTV_DESC_TEXT_MOVIE_DURATION_W (IPTV_DESC_TEXT_MOVIE_YEAR_W)
#define IPTV_DESC_TEXT_MOVIE_DURATION_H  (IPTV_DESC_MOVIE_TXT_YEAR_H)

// movie txt duration
#define IPTV_DESC_MOVIE_TXT_DURATION_X  (IPTV_DESC_TEXT_MOVIE_DURATION_X + IPTV_DESC_TEXT_MOVIE_DURATION_W + 20)
#define IPTV_DESC_MOVIE_TXT_DURATION_Y   IPTV_DESC_TEXT_MOVIE_DURATION_Y
#define IPTV_DESC_MOVIE_TXT_DURATION_W   (730 - IPTV_DESC_MOVIE_TXT_DURATION_X)
#define IPTV_DESC_MOVIE_TXT_DURATION_H   (IPTV_DESC_TEXT_MOVIE_DURATION_H)


// movie direction
#define IPTV_DESC_TEXT_MOVIE_DIRECTER_X  (IPTV_DESC_TEXT_MOVIE_YEAR_X)
#define IPTV_DESC_TEXT_MOVIE_DIRECTER_Y  (IPTV_DESC_TEXT_MOVIE_YEAR_Y + IPTV_DESC_TEXT_MOVIE_YEAR_H +  IPTV_DESC_TEXT_VERTICAL)
#define IPTV_DESC_TEXT_MOVIE_DIRECTER_W (IPTV_DESC_TEXT_MOVIE_YEAR_W)
#define IPTV_DESC_TEXT_MOVIE_DIRECTER_H  (IPTV_DESC_TEXT_MOVIE_YEAR_H)

// movie direction
#define IPTV_DESC_MOVIE_TXT_DIRECTER_X  (30 + IPTV_DESC_TEXT_MOVIE_ACTOR_W + IPTV_DESC_TEXT_INTERVAL)
#define IPTV_DESC_MOVIE_TXT_DIRECTER_Y  (IPTV_DESC_TEXT_MOVIE_DIRECTER_Y)
#define IPTV_DESC_MOVIE_TXT_DIRECTER_W  (730 - IPTV_DESC_MOVIE_TXT_ACTOR_X )
#define IPTV_DESC_MOVIE_TXT_DIRECTER_H   (IPTV_DESC_TEXT_MOVIE_DIRECTER_H)


// movie actor
#define IPTV_DESC_TEXT_MOVIE_ACTOR_X  (IPTV_DESC_TEXT_MOVIE_YEAR_X)
#define IPTV_DESC_TEXT_MOVIE_ACTOR_Y  (IPTV_DESC_TEXT_MOVIE_DIRECTER_Y + IPTV_DESC_TEXT_MOVIE_DIRECTER_H)
#define IPTV_DESC_TEXT_MOVIE_ACTOR_W (IPTV_DESC_TEXT_MOVIE_YEAR_W)
#define IPTV_DESC_TEXT_MOVIE_ACTOR_H  (IPTV_DESC_TEXT_MOVIE_YEAR_H)

//movie actor txt 
#define IPTV_DESC_MOVIE_TXT_ACTOR_X  (30 + IPTV_DESC_TEXT_MOVIE_ACTOR_W + IPTV_DESC_TEXT_INTERVAL)
#define IPTV_DESC_MOVIE_TXT_ACTOR_Y  (IPTV_DESC_TEXT_MOVIE_ACTOR_Y)
#define IPTV_DESC_MOVIE_TXT_ACTOR_W (730 - IPTV_DESC_MOVIE_TXT_ACTOR_X )
#define IPTV_DESC_MOVIE_TXT_ACTOR_H  (IPTV_DESC_TEXT_MOVIE_ACTOR_H)


//description text title
#define IPTV_DESC_MOVIE_TEXT_TITLE_X  (IPTV_DESC_TEXT_MOVIE_YEAR_X)
#define IPTV_DESC_MOVIE_TEXT_TITLE_Y  (IPTV_DESC_TEXT_MOVIE_ACTOR_Y + IPTV_DESC_TEXT_MOVIE_ACTOR_H )
#define IPTV_DESC_MOVIE_TEXT_TITLE_W (IPTV_DESC_TEXT_MOVIE_YEAR_W)
#define IPTV_DESC_MOVIE_TEXT_TITLE_H  (IPTV_DESC_TEXT_MOVIE_YEAR_H)

//description text
#define IPTV_DESC_MOVIE_TEXT_X  (IPTV_DESC_MOVIE_TEXT_TITLE_X + IPTV_DESC_MOVIE_TEXT_TITLE_W + 20)
#define IPTV_DESC_MOVIE_TEXT_Y  IPTV_DESC_MOVIE_TEXT_TITLE_Y
#define IPTV_DESC_MOVIE_TEXT_W  (765 - IPTV_DESC_MOVIE_TEXT_X)
#define IPTV_DESC_MOVIE_TEXT_H  155



//vodeo rsc mbox
#define  IPTV_MOVIE_RSC_MBOX_X  90
#define  IPTV_MOVIE_RSC_MBOX_Y  (IPTV_DESC_MOVIE_TEXT_Y + IPTV_DESC_MOVIE_TEXT_H + 10)
#define  IPTV_MOVIE_RSC_MBOX_W  280
#define  IPTV_MOVIE_RSC_MBOX_H  COMM_CTRL_H
#define IPTV_MOVIE_RSC_INTERVAL 40
//variety rsc list
/* others */
#define IPTV_VARIETY_REVIEW_RSC_LIST_PAGE    (10)
#define IPTV_VARIETY_REVIEW_RSC_LIST_FIELD   (1)
#define IPTV_VARIETY_REVIEW_RSC_ITEM_VGAP    (4)

#define  IPTV_VARIETY_REVIEW_RSC_LIST_X  	(0)
#define  IPTV_VARIETY_REVIEW_RSC_LIST_Y  	(0)
#define  IPTV_VARIETY_REVIEW_RSC_LIST_W 	(IPTV_VARIETY_RSC_LIST_W)
#define  IPTV_VARIETY_REVIEW_RSC_LIST_H 	(IPTV_VARIETY_RSC_LIST_H)

#define IPTV_VARIETY_REVIEW_RSC_LIST_MID_L  (4)
#define IPTV_VARIETY_REVIEW_RSC_LIST_MID_T  (4)
#define IPTV_VARIETY_REVIEW_RSC_LIST_MID_W  (IPTV_VARIETY_REVIEW_RSC_LIST_W - 2 * IPTV_VARIETY_REVIEW_RSC_LIST_MID_L)
#define IPTV_VARIETY_REVIEW_RSC_LIST_MID_H  ((41 + IPTV_VARIETY_REVIEW_RSC_ITEM_VGAP) * IPTV_VARIETY_REVIEW_RSC_LIST_PAGE - IPTV_VARIETY_REVIEW_RSC_ITEM_VGAP)//482


#define IPTV_VARIETY_REVIEW_DAY_RSC_LIST_PAGE    (7)
#define IPTV_VARIETY_REVIEW_DAY_RSC_LIST_FIELD   (2)

#define  IPTV_VARIETY_REVIEW_DAY_RSC_LIST_X  	(0)
#define  IPTV_VARIETY_REVIEW_DAY_RSC_LIST_Y  	(0)
#define  IPTV_VARIETY_REVIEW_DAY_RSC_LIST_W 	(IPTV_VARIETY_RSC_CONTENT_CNTW)
#define  IPTV_VARIETY_REVIEW_DAY_RSC_LIST_H 	(IPTV_VARIETY_RSC_CONTENT_CNTH)

#define  IPTV_VARIETY_REVIEW_RSC_TEXT_X 	(550)
#define  IPTV_VARIETY_REVIEW_RSC_TEXT_Y  	(490)
#define  IPTV_VARIETY_REVIEW_RSC_TEXT_W 	(100)
#define  IPTV_VARIETY_REVIEW_RSC_TEXT_H 	(40)

#define  IPTV_VARIETY_REVIEW_RSC_PER_X 		(650)
#define  IPTV_VARIETY_REVIEW_RSC_PER_Y  	(490)
#define  IPTV_VARIETY_REVIEW_RSC_PER_W 		(100)
#define  IPTV_VARIETY_REVIEW_RSC_PER_H 		(40)



#define IPTV_VARIETY_RSC_LIST_PAGE    10
#define IPTV_VARIETY_RSC_LIST_FIELD   1

#define  IPTV_VARIETY_RSC_LIST_X 0
#define  IPTV_VARIETY_RSC_LIST_Y  0
#define  IPTV_VARIETY_RSC_LIST_W 785
#define  IPTV_VARIETY_RSC_LIST_H 490

#define  IPTV_VARIETY_RSC_SBAR_X IPTV_VARIETY_RSC_LIST_X+IPTV_VARIETY_RSC_LIST_W-IPTV_VARIETY_RSC_SBAR_W
#define  IPTV_VARIETY_RSC_SBAR_Y  IPTV_VARIETY_RSC_LIST_Y
#define  IPTV_VARIETY_RSC_SBAR_W 6
#define  IPTV_VARIETY_RSC_SBAR_H IPTV_VARIETY_RSC_LIST_H

#define IPTV_VARIETY_RSC_LIST_MID_L     4
#define IPTV_VARIETY_RSC_LIST_MID_T     4
#define IPTV_VARIETY_RSC_LIST_MID_W   (IPTV_VARIETY_RSC_LIST_W - 2 * IPTV_VARIETY_RSC_LIST_MID_L)
#define IPTV_VARIETY_RSC_LIST_MID_H    ((41 + IPTV_VARIETY_RSC_ITEM_VGAP) * IPTV_VARIETY_RSC_LIST_PAGE - IPTV_VARIETY_RSC_ITEM_VGAP)//482

#define  IPTV_VARIETY_RSC_TEXT_X 550
#define  IPTV_VARIETY_RSC_TEXT_Y  490
#define  IPTV_VARIETY_RSC_TEXT_W 100
#define  IPTV_VARIETY_RSC_TEXT_H 40

#define  IPTV_VARIETY_RSC_PER_X 650
#define  IPTV_VARIETY_RSC_PER_Y  490
#define  IPTV_VARIETY_RSC_PER_W 100
#define  IPTV_VARIETY_RSC_PER_H 40

#define IPTV_VARIETY_RSC_ITEM_H        COMM_ITEM_H
#define IPTV_VARIETY_RSC_ITEM_VGAP    4

//desc variety content
#define IPTV_VARIETY_RSC_CONTENT_CNTX IPTV_DESC_PICTUREX
#define IPTV_VARIETY_RSC_CONTENT_CNTY IPTV_DESC_PICTUREY + IPTV_DESC_PICTUREH
#define IPTV_VARIETY_RSC_CONTENT_CNTW IPTV_DESC_PICTUREW
#define IPTV_VARIETY_RSC_CONTENT_CNTH 220

//variety description text title
#define IPTV_VARIETY_RSC_TEXT_TITLE_X  10
#define IPTV_VARIETY_RSC_TEXT_TITLE_Y  5
#define IPTV_VARIETY_RSC_TEXT_TITLE_W  50
#define IPTV_VARIETY_RSC_TEXT_TITLE_H  30

//variety description text title
#define IPTV_VARIETY_RSC_TEXT_DES_X  10 + IPTV_VARIETY_RSC_TEXT_TITLE_W + 10
#define IPTV_VARIETY_RSC_TEXT_DES_Y  5
#define IPTV_VARIETY_RSC_TEXT_DES_W  200
#define IPTV_VARIETY_RSC_TEXT_DES_H  120

//variety description text title
#define IPTV_VARIETY_RSC_TENT_BUN_X  25
#define IPTV_VARIETY_RSC_TENT_BUN_Y  160
#define IPTV_VARIETY_RSC_TENT_BUN_W  120
#define IPTV_VARIETY_RSC_TENT_BUN_H  COMM_CTRL_H

//variety description text ori url title
#define IPTV_VARIETY_RSC_TENT_URL_TITLE_X  IPTV_VARIETY_RSC_TENT_BUN_X+IPTV_VARIETY_RSC_TENT_BUN_W+20
#define IPTV_VARIETY_RSC_TENT_URL_TITLE_Y  160
#define IPTV_VARIETY_RSC_TENT_URL_TITLE_W  120
#define IPTV_VARIETY_RSC_TENT_URL_TITLE_H  COMM_CTRL_H


#define IPTV_MOVIE_RSC_ITEM 3
#define IPTV_MOVIE_RSC_COL 3
#define IPTV_MOVIE_RSC_ROW  1

#define IPTV_ORIGINS_MAX      10
#define IPTV_SCROLL_BAR_MAX 6
#define IPTV_GET_PAGE_SIZE 0xa
#define IPTV_URL_LEN_MAX    512
#define IPTV_FORMAT_MAX      10


typedef enum{
	IPTV_DESC_INIT,
	IPTV_DESC_INFO_ARRIVE,
	IPTV_DESC_URL_ARRIVE,
	IPTV_DESC_RECOMM_ARRIVE,
	IPTV_DESC_DEINIT,
	IPTV_DESC_DESTORY,
}ui_iptv_state_t;

u8 get_iptv_des_state(void);
void set_iptv_des_state(u8 state);


void ui_iptvdesc_get_info_url(u8  category, u16 episode_num,VDO_ID_t *vdo_id);
u16 *ui_iptvdesc_get_episode_name(u8 category, u16 episode_num);

#endif

