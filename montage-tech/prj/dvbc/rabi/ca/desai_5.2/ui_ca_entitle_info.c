/****************************************************************************
* Notice:      Copyright (c) Montage Techonoloy Corporation (2009).
*              All rights reserved.
* Owner:       Kevin Li <kai.li@montage-tech.com>
*              Mark Wu <mark.wu@montage-tech.com>
****************************************************************************/
#include "ui_common.h"
#include "ui_ca_entitle_info.h"
#include "ui_ca_public.h"

enum control_id
{
    IDC_INVALID = 0,
    IDC_CA_INFO_HEAD_CONT,  
    IDC_CA_INFO_HEAD,  
    IDC_CA_INFO_LIST_CONT,
    IDC_CA_INFO_LIST_ENTITLE,
};

static list_xstyle_t ca_info_item_rstyle =
{
    RSI_PBACK,
    RSI_COMM_CONT_SH,
    RSI_SELECT_F,
    RSI_SELECT_F,
    RSI_SELECT_F,
};
static list_xstyle_t ca_info_field_fstyle =
{
    FSI_WHITE,
    FSI_WHITE,
    FSI_WHITE,
    FSI_WHITE,
    FSI_WHITE,
};
static list_xstyle_t ca_info_field_rstyle =
{
    RSI_PBACK,
    RSI_PBACK,
    RSI_IGNORE,
    RSI_IGNORE,
    RSI_IGNORE,
};
static list_field_attr_t ca_info_list_entitle_attr[ENTITLE_INFO_LIST_FIELD] =
{
    { LISTFIELD_TYPE_DEC| STL_LEFT | STL_VCENTER,
      80, 45, 0, &ca_info_field_rstyle,  &ca_info_field_fstyle },

    { LISTFIELD_TYPE_UNISTR| STL_CENTER| STL_VCENTER,
      500, 300, 0, &ca_info_field_rstyle,  &ca_info_field_fstyle },
};

static product_entitles_info_t *p_entitle = NULL;

RET_CODE ca_info_proc(control_t *p_ctrl, u16 msg, u32 para1, u32 para2);
u16 ca_info_list_keymap(u16 key);
RET_CODE ca_info_list_proc(control_t *p_ctrl, u16 msg, u32 para1, u32 para2);

static RET_CODE ca_info_list_entitle_update(control_t *p_list, u16 start, u16 size, u32 context)
{
    u16 i, cnt = list_get_count(p_list);
    u8 asc_str[64] = {0};
    s32 product_id = 0;

    for (i = 0; i < size; i++)
    {
        if (i + start < cnt)
        {
            product_id = (s32)p_entitle->p_entitle_info[i + start].product_id;
            list_set_field_content_by_dec(p_list, (u16)(start + i), 0, product_id); 

            sprintf((char *)asc_str,"%04d/%02d/%02d %02d:%02d:%02d ~ %04d/%02d/%02d %02d:%02d:%02d",
                                    p_entitle->p_entitle_info[i + start].start_time[0]*256 + 
                                    p_entitle->p_entitle_info[i + start].start_time[1], 
                                    p_entitle->p_entitle_info[i + start].start_time[2],
                                    p_entitle->p_entitle_info[i + start].start_time[3],
                                    p_entitle->p_entitle_info[i + start].start_time[4],
                                    p_entitle->p_entitle_info[i + start].start_time[5],
                                    p_entitle->p_entitle_info[i + start].start_time[6],
                                    p_entitle->p_entitle_info[i + start].expired_time[0]*256 + p_entitle->p_entitle_info[i + start].expired_time[1],
                                    p_entitle->p_entitle_info[i + start].expired_time[2],
                                    p_entitle->p_entitle_info[i + start].expired_time[3],
                                    p_entitle->p_entitle_info[i + start].expired_time[4],
                                    p_entitle->p_entitle_info[i + start].expired_time[5],
                                    p_entitle->p_entitle_info[i + start].expired_time[6]);
            list_set_field_content_by_ascstr(p_list, (u16)(start + i), 1, asc_str);         
        }
     }
    return SUCCESS;
}



RET_CODE open_ca_entitle_info(u32 para1, u32 para2)
{
    control_t *p_cont, *p_list, *p_mbox;
    u8 i;
    u16 itemmenu_btn_str[ENTITLE_INFO_ITME_COUNT] =
    {
        IDS_CA_PRODUCT_ID, IDS_CA_AUTHORIZE_DEADLINE
    };
  
    // create container
    p_cont = ui_comm_right_root_create(ROOT_ID_CA_ENTITLE_INFO, ROOT_ID_CA_OPERATOR_INFO, OBJ_ATTR_ACTIVE, 0);

    if(p_cont == NULL)
    {
        return ERR_FAILURE;
    }
    ctrl_set_keymap(p_cont, ui_comm_root_keymap);
    ctrl_set_proc(p_cont, ca_info_proc);

    //mbox item title
    p_mbox = ctrl_create_ctrl(CTRL_MBOX, (u8)IDC_CA_INFO_HEAD,
                            ENTITLE_INFO_MBOX_X, ENTITLE_INFO_MBOX_Y, 
                            ENTITLE_INFO_MBOX_W, ENTITLE_INFO_MBOX_H,
                            p_cont, 0);
    ctrl_set_rstyle(p_mbox, RSI_PBACK, RSI_PBACK, RSI_PBACK);
    ctrl_set_attr(p_mbox, OBJ_ATTR_ACTIVE);
    mbox_set_focus(p_mbox, 1);
    mbox_enable_string_mode(p_mbox, TRUE);
    mbox_set_content_strtype(p_mbox, MBOX_STRTYPE_STRID);
    mbox_set_count(p_mbox, ENTITLE_INFO_ITME_COUNT, ENTITLE_INFO_ITME_COUNT, 1);
    mbox_set_string_fstyle(p_mbox, FSI_WHITE, FSI_WHITE, FSI_WHITE);
    mbox_set_string_offset(p_mbox, ENTITLE_INFO_PRODUCT_ID_ITEM_OFFSET, 0);
    mbox_set_string_align_type(p_mbox, STL_LEFT| STL_VCENTER);
    for (i = 0; i < ENTITLE_INFO_ITME_COUNT; i++)
    {
        mbox_set_content_by_strid(p_mbox, i, itemmenu_btn_str[i]);
    }
  
    p_list = ctrl_create_ctrl(CTRL_LIST, IDC_CA_INFO_LIST_ENTITLE,
                           ENTITLE_INFO_PLIST_X, ENTITLE_INFO_PLIST_Y, ENTITLE_INFO_PLIST_W,ENTITLE_INFO_PLIST_H, p_cont, 0);
    ctrl_set_rstyle(p_list, RSI_PBACK, RSI_PBACK, RSI_PBACK);
    ctrl_set_keymap(p_list, ca_info_list_keymap);
    ctrl_set_proc(p_list, ca_info_list_proc);

    ctrl_set_mrect(p_list, ENTITLE_INFO_LIST_MIDL, ENTITLE_INFO_LIST_MIDT,
                 ENTITLE_INFO_LIST_MIDL + ENTITLE_INFO_LIST_MIDW, ENTITLE_INFO_LIST_MIDT + ENTITLE_INFO_LIST_MIDH);
    list_set_item_rstyle(p_list, &ca_info_item_rstyle);
    list_set_count(p_list, 0, ENTITLE_INFO_LIST_PAGE);
    list_set_field_count(p_list, ENTITLE_INFO_LIST_FIELD, ENTITLE_INFO_LIST_PAGE);
    list_set_focus_pos(p_list, 1);
    list_set_update(p_list, ca_info_list_entitle_update, 0);
 
    for (i = 0; i < ENTITLE_INFO_LIST_FIELD; i++)
    {
        list_set_field_attr(p_list, (u8)i,
                            (u32)(ca_info_list_entitle_attr[i].attr),
                            (u16)(ca_info_list_entitle_attr[i].width),
                            (u16)(ca_info_list_entitle_attr[i].left),
                            (u8)(ca_info_list_entitle_attr[i].top));
        list_set_field_rect_style(p_list, (u8)i,
                            ca_info_list_entitle_attr[i].rstyle);
        list_set_field_font_style(p_list, (u8)i,
                            ca_info_list_entitle_attr[i].fstyle);
    }  
#ifndef WIN32 
    ui_ca_do_cmd(CAS_CMD_ENTITLE_INFO_GET, 0, 0);
#else
    on_ca_info_entitle(p_cont, 0, 0, para1);
#endif
    ctrl_default_proc(p_list, MSG_GETFOCUS, 0, 0);  
    ctrl_paint_ctrl(p_cont, FALSE);
    return SUCCESS;
  
}

static RET_CODE on_ca_info_entitle(control_t *p_cont, u16 msg, u32 para1, u32 para2)
{
    control_t *p_list = ctrl_get_child_by_id(p_cont, IDC_CA_INFO_LIST_ENTITLE);

    p_entitle = (product_entitles_info_t *)para2;
    list_set_count(p_list, p_entitle->max_num, ENTITLE_INFO_LIST_PAGE);
    list_set_focus_pos(p_list, 0);
    ca_info_list_entitle_update(p_list, list_get_valid_pos(p_list), ENTITLE_INFO_LIST_PAGE, 0);

    ctrl_paint_ctrl(p_list, TRUE);
    return SUCCESS;
}
static RET_CODE on_ca_info_save(control_t *p_cont, u16 msg, u32 para1, u32 para2)
{
    p_entitle = NULL;
    return SUCCESS;
}

BEGIN_MSGPROC(ca_info_proc, ui_comm_root_proc)
    ON_COMMAND(MSG_CA_ENT_INFO, on_ca_info_entitle)
    ON_COMMAND(MSG_SAVE, on_ca_info_save)
END_MSGPROC(ca_info_proc, ui_comm_root_proc)

BEGIN_KEYMAP(ca_info_list_keymap, NULL)
    ON_EVENT(V_KEY_UP, MSG_FOCUS_UP)    
    ON_EVENT(V_KEY_DOWN, MSG_FOCUS_DOWN)
    ON_EVENT(V_KEY_PAGE_UP, MSG_PAGE_UP)
    ON_EVENT(V_KEY_PAGE_DOWN, MSG_PAGE_DOWN)
END_KEYMAP(ca_info_list_keymap, NULL)

BEGIN_MSGPROC(ca_info_list_proc, list_class_proc)

END_MSGPROC(ca_info_list_proc, list_class_proc)


