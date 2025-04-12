//
// Generated by dtk
// Translation Unit: d_a_tag_msg.cpp
//

#include "d/actor/d_a_tag_msg.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep

static fpc_ProcID l_msgId;
static msg_class* l_msg;
static u8 msg_mode;

/* 00000078-00000084       .text getEventNo__11daTag_Msg_cFv */
u32 daTag_Msg_c::getEventNo() {
    return base.mParameters >> 0x18;
}

/* 00000084-00000090       .text getSwbit__11daTag_Msg_cFv */
u32 daTag_Msg_c::getSwbit() {
    return base.mParameters >> 8 & 0xff;
}

/* 00000090-0000009C       .text getSwbit2__11daTag_Msg_cFv */
u32 daTag_Msg_c::getSwbit2() {
    return base.mParameters >> 0x10 & 0xff;
}

/* 0000009C-000000A8       .text getType2__11daTag_Msg_cFv */
u32 daTag_Msg_c::getType2() {
    return base.mParameters >> 6 & 3;
}

/* 000000A8-0000015C       .text myDemoName__11daTag_Msg_cFv */
const char* daTag_Msg_c::myDemoName() {
    dStage_EventInfo_c *pEventInfo;
    u32 eventNo;

    pEventInfo = dComIfGp_getStageEventInfo();
    eventNo = getEventNo() & 0xff;

    if (getMessage() == 0x1902) {
        return "RT_TALK";
    }
    if (pEventInfo == NULL || (int)eventNo == 0xff || pEventInfo->num < (int)eventNo) {
        return "DEFAULT_MSG";
    }
    return pEventInfo->events[eventNo].mName;
}

/* 0000015C-00000168       .text getMessage__11daTag_Msg_cFv */
u16 daTag_Msg_c::getMessage() {
    return home.angle.x;
}

/* 00000168-00000174       .text getEventFlag__11daTag_Msg_cFv */
u16 daTag_Msg_c::getEventFlag() {
    return home.angle.z;
}

/* 00000174-0000021C       .text arrivalTerms__11daTag_Msg_cFv */
BOOL daTag_Msg_c::arrivalTerms() {
    int swBit;
    u16 eventFlag;
    swBit = (int)(getSwbit2() & 0xFF);
    eventFlag = getEventFlag();
    if ((s32)swBit != 0xff && dComIfGs_isSwitch(swBit, current.roomNo) == 0) {
        return FALSE;
    }
    else if (eventFlag != 0xffff && dComIfGs_isEventBit(eventFlag) == 0) {
        return FALSE;
    }
    else {
        return TRUE;
    }
}

/* 0000021C-000002FC       .text rangeCheck__11daTag_Msg_cFv */
BOOL daTag_Msg_c::rangeCheck() {
    daPy_lk_c* link;
    cXyz diff;

    link = daPy_getPlayerLinkActorClass();
    diff = link->current.pos - current.pos;

    if (diff.y < 0.0f) {
        diff.y = -diff.y;
    }
    if (diff.abs2XZ() < scale.x * scale.x * 10000.0f) {
        if(diff.y <= scale.y * 100.0f) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 000002FC-0000041C       .text otherCheck__11daTag_Msg_cFv */
BOOL daTag_Msg_c::otherCheck() {
    s16 targetAngle = fopAcM_searchPlayerAngleY(this);
    daPy_lk_c* player = daPy_getPlayerLinkActorClass();
    if (getType2() & 1) {
        return TRUE;
    }
    JUT_ASSERT(0xC8, player);
    if (getMessage() == 0x1902) {
        s16 diff = targetAngle - home.angle.y;
        if (diff < 0) {
            diff = -diff;
        }
        if (0x3000 < diff) {
            return FALSE;
        }
    }
    targetAngle = (s16)(targetAngle + 0x7FFF) - player->current.angle.y;
    if (targetAngle < 0) {
        targetAngle = -targetAngle;
    }
    if (targetAngle > 0x1000) {
        return FALSE;
    }

    return TRUE;
}

/* 0000041C-0000065C       .text daTag_Msg_actionEvent__FP11daTag_Msg_c */
static BOOL daTag_Msg_actionEvent(daTag_Msg_c* a_this) {
    int message = a_this->getMessage();
    switch (msg_mode / 1) {
    case 0:
        if (dComIfGp_checkCameraAttentionStatus(dComIfGp_getPlayerCameraID(0), 4)) {
            msg_mode++;
        }
        break;
    case 1:
        l_msgId = fopMsgM_messageSet(message, &a_this->attention_info.position);
        if (l_msgId != fpcM_ERROR_PROCESS_ID_e) {
            msg_mode++;
        }
        break;
    case 2:
        l_msg = fopMsgM_SearchByID(l_msgId);
        if (l_msg != NULL) {
            msg_mode++;
        }
        break;
    case 3:
        JUT_ASSERT(0x13F, l_msg);
        if (l_msg->mStatus == fopMsgStts_MSG_TYPING_e) {
            msg_mode++;
        }
        break;
    case 4:
        JUT_ASSERT(0x145, l_msg);
        if (l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            msg_mode++;
            l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
        }
        break;
    }
    if (l_msg != NULL && l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
        dComIfGp_event_reset();
        if (a_this->getMessage() == 0x1902) {
            daPy_getPlayerLinkActorClass()->offPlayerNoDraw();
        }
        if (a_this->getType2() & 1) {
            a_this->setActio(0);
        } else {
            a_this->setActio(2);
        }
    }
    return TRUE;
}

/* 0000065C-00000754       .text daTag_Msg_actionHunt__FP11daTag_Msg_c */
static BOOL daTag_Msg_actionHunt(daTag_Msg_c* a_this) {
    u8 swBit;

    if (a_this->eventInfo.mCommand == dEvtCmd_INTALK_e) {
        a_this->setActio(3);
        swBit = a_this->getSwbit();
        if ((swBit & 0xff) != 0xff) {
            dComIfGs_onSwitch(swBit,a_this->current.roomNo);
        }
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        l_msg = 0;
        msg_mode = 0;
        if ((u32)a_this->getMessage() == 0x1902) {
            daPy_getPlayerLinkActorClass()->onPlayerNoDraw();
        }
    } else if (a_this->rangeCheck() != 0 && a_this->otherCheck() != 0) {
        if (a_this->getType2() & 1) {
            fopAcM_orderSpeakEvent(a_this);
        }
        a_this->eventInfo.onCondition(dEvtCnd_CANTALK_e);
    }
    return TRUE;
}

/* 00000754-000007B0       .text daTag_Msg_actionArrival__FP11daTag_Msg_c */
static BOOL daTag_Msg_actionArrival(daTag_Msg_c* a_this) {
    char *cutsceneName;

    if (a_this->arrivalTerms() != 0) {
        cutsceneName = (char*)a_this->myDemoName();
        a_this->eventInfo.setEventName(cutsceneName);
        a_this->setActio(2);
        daTag_Msg_actionHunt(a_this);
    }
    return TRUE;
}

/* 000007B0-000007B8       .text daTag_Msg_actionWait__FP11daTag_Msg_c */
static BOOL daTag_Msg_actionWait(daTag_Msg_c*) {
    return TRUE;
}

/* 000007B8-000007C0       .text daTag_Msg_Draw__FP11daTag_Msg_c */
static BOOL daTag_Msg_Draw(daTag_Msg_c*) {
    return TRUE;
}

BOOL daTag_Msg_c::execute() {
    static ActionFunc* l_action[4] = {
        daTag_Msg_actionWait,
        daTag_Msg_actionArrival,
        daTag_Msg_actionHunt,
        daTag_Msg_actionEvent,
    };
    l_action[mAction](this);
    return TRUE;
}

cPhs_State daTag_Msg_c::create() {
    int swBit;
    fopAcM_SetupActor(this, daTag_Msg_c);
    swBit = (int)(getSwbit() & 0xFF);
    if ((getMessage() == 0x9c5) && dComIfGs_isEventBit(0x502)) {
        setActio(0);
    } else if ((s32)swBit != 0xff && dComIfGs_isSwitch(swBit, current.roomNo) != 0) {
        setActio(0);
    } else {
        setActio(1);
    }
    shape_angle.z = 0;
    shape_angle.x = 0;
    current.angle.z = 0;
    current.angle.x = 0;
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_CHECK_e;
    if (getMessage() != 0x836) {
        attention_info.position.y += 150;
        eyePos.y += 150.0f;
    }
    return cPhs_COMPLEATE_e;
}

/* 000007C0-000007FC       .text daTag_Msg_Execute__FP11daTag_Msg_c */
static BOOL daTag_Msg_Execute(daTag_Msg_c* a_this) {
    return a_this->execute();
}

/* 000007FC-00000804       .text daTag_Msg_IsDelete__FP11daTag_Msg_c */
static BOOL daTag_Msg_IsDelete(daTag_Msg_c*) {
    return TRUE;
}

/* 00000804-00000834       .text daTag_Msg_Delete__FP11daTag_Msg_c */
static BOOL daTag_Msg_Delete(daTag_Msg_c* a_this) {
    a_this->~daTag_Msg_c();
    return TRUE;
}

/* 00000834-00000964       .text daTag_Msg_Create__FP10fopAc_ac_c */
static cPhs_State daTag_Msg_Create(fopAc_ac_c* i_this) {
    daTag_Msg_c* a_this = (daTag_Msg_c*)i_this;
    return a_this->create();
}

static actor_method_class l_daTag_Msg_Method = {
    (process_method_func)daTag_Msg_Create,
    (process_method_func)daTag_Msg_Delete,
    (process_method_func)daTag_Msg_Execute,
    (process_method_func)daTag_Msg_IsDelete,
    (process_method_func)daTag_Msg_Draw,
};

actor_process_profile_definition g_profile_TAG_MSG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TAG_MSG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTag_Msg_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0121,
    /* Actor SubMtd */ &l_daTag_Msg_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_6_e,
};
