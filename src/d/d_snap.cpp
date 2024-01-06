//
// Generated by dtk
// Translation Unit: d_snap.cpp
//

#include "d/d_snap.h"
#include "d/d_com_inf_game.h"
#include "f_pc/f_pc_manager.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_lib.h"
#include "JSystem/JUtility/JUTAssert.h"

// Needed for the .rodata section to match.
static const f32 dummy_2080[3] = {1.0f, 1.0f, 1.0f};
static const f32 dummy_2100[3] = {1.0f, 1.0f, 1.0f};
static const f32 dummy_3599[3] = {0.0f, 0.0f, 0.0f};

int (dSnap_packet::*dSnap_packet::m_judge_tbl[])() = {
    NULL,
    &dSnap_packet::JudgePost,
    &dSnap_packet::JudgeBikutsuki,
    &dSnap_packet::JudgeCoupleLook,
    &dSnap_packet::JudgeGF,
    &dSnap_packet::JudgeGenzo,
    &dSnap_packet::JudgeObasan4,
    &dSnap_packet::JudgeGene,
    &dSnap_packet::JudgeGene,
    &dSnap_packet::JudgeGene,
    &dSnap_packet::JudgeTestM,
};
dSnap_packet l_snap;

struct CharaData {
    /* 0x00 */ SVec offset;
    /* 0x06 */ s16 radius;
    /* 0x08 */ s16 height;
    /* 0x0A */ u16 m0A;
    /* 0x0C */ s16 m0C;
    /* 0x0E */ u16 m0E;
    /* 0x10 */ u8 room;
};  // Size: 0x12

static const CharaData l_CharaData[0x86] = {
    // TODO
};

static const int CharaDataTblSize = 0x86;
static const int DSNAP_TYPE_LAST_INDEX = 0xD0;

static const Vec cylvtx[5] = {
    // TODO
};
static const Vec vdata[12] = {
    // TODO
};
static const int tindices[20][3] = {
    // TODO
};

/* 800CCF6C-800CCFE4       .text dSnap_PhotoIndex2TableIndex__Fi */
int dSnap_PhotoIndex2TableIndex(int photoIndex) {
    int index = photoIndex - 0x49;
    JUT_ASSERT(334, index >= 0 && index < CharaDataTblSize);
    return index;
}

/* 800CCFE4-800CD00C       .text dSnap_GetFigRoomId__Fi */
u8 dSnap_GetFigRoomId(int r3) {
    if (r3 >= 0x86) {
        return 0xFF;
    }
    return l_CharaData[r3].room;
}

/* 800CD00C-800CD068       .text __ct__9dSnap_ObjFv */
dSnap_Obj::dSnap_Obj() {
    mActorPID = fpcM_ERROR_PROCESS_ID_e;
    mPhoto = 0;
    field_0x19 = 4;
    field_0x1a = -1;
    field_0x1b = 0;
    field_0x1c = 0x7FFF;
    mAngleY = 0;
    field_0x20 = 0;
    field_0x24 = 0.0f;
    mMinX = 0;
    mMinY = 0;
    mMaxX = 0;
    mMaxY = 0;
}

/* 800CD068-800CD6D0       .text CalcArea2D__9dSnap_ObjFv */
f32 dSnap_Obj::CalcArea2D() {
    /* Nonmatching */
    f32 f28 = 0.0f;
    f32 f29 = mRadius;
    f32 f30 = mHeight;
    cXyz sp8c;
    cXyz sp80;
    cXyz sp74;
    cXyz sp68;
    cXyz sp5c;
    cXyz sp50;
    cXyz sp44;
    cXyz sp38;
    cXyz sp2c;
    cXyz sp20;
    cXyz sp14;
    cXyz sp8;
    f32 f0;
    
    if (!(field_0x1b & 1)) {
        mDoMtx_stack_c::transS(mCenter);
        mDoMtx_stack_c::scaleM(f29, f30, f29);
        mDoMtx_stack_c::YrotM(mAngleY);
        sp44.set(0.0f, 0.0f, 0.0f);
        mDoMtx_stack_c::multVec(&sp44, &sp44);
        sp38.set(0.0f, 1.0f, 0.0f);
        mDoMtx_stack_c::multVec(&sp38, &sp38);
        
        for (int i = 0; i < field_0x19; i++) {
            sp8c.x = cylvtx[i].x;
            sp8c.y = 0.0f;
            sp8c.z = cylvtx[i].z;
            
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp74);
            sp8c.y = 1.0f;
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp68);
            
            sp8c.x = cylvtx[i+1].x;
            sp8c.z = cylvtx[i+1].z;
            
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp5c);
            sp8c.y = 0.0f;
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp50);
            
            f0 = 0.5f * ((sp68.x - sp74.x) * (sp5c.y - sp74.y) - (sp68.y - sp74.y) * (sp5c.x - sp74.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            f0 = 0.5f * ((sp5c.x - sp74.x) * (sp50.y - sp74.y) - (sp5c.y - sp74.y) * (sp50.x - sp74.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            
            mDoLib_project(&sp38, &sp2c);
            f0 = 0.5f * ((sp5c.x - sp2c.x) * (sp68.y - sp2c.y) - (sp5c.y - sp2c.y) * (sp68.x - sp2c.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            mDoLib_project(&sp44, &sp20);
            f0 = 0.5f * ((sp74.x - sp20.x) * (sp50.y - sp20.y) - (sp74.y - sp20.y) * (sp50.x - sp20.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            
            sp8c.x = -cylvtx[i].x;
            sp8c.y = 1.0f;
            sp8c.z = cylvtx[i].z;
            
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp74);
            sp8c.y = 0.0f;
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp68);
            
            sp8c.x = -cylvtx[i+1].x;
            sp8c.z = cylvtx[i+1].z;
            
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp5c);
            sp8c.y = 1.0f;
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp50);
            
            f0 = 0.5f * ((sp68.x - sp74.x) * (sp5c.y - sp74.y) - (sp68.y - sp74.y) * (sp5c.x - sp74.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            f0 = 0.5f * ((sp5c.x - sp74.x) * (sp50.y - sp74.y) - (sp5c.y - sp74.y) * (sp50.x - sp74.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            
            mDoLib_project(&sp38, &sp14);
            f0 = 0.5f * ((sp74.x - sp14.x) * (sp50.y - sp14.y) - (sp74.y - sp14.y) * (sp50.x - sp14.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
            
            mDoLib_project(&sp44, &sp8);
            f0 = 0.5f * ((sp5c.x - sp8.x) * (sp68.y - sp8.y) - (sp5c.y - sp8.y) * (sp68.x - sp8.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
        }
    } else {
        mDoMtx_stack_c::transS(mCenter);
        mDoMtx_stack_c::scaleM(f29, f29, f29);
        
        for (int i = 0; i < 0x14; i++) {
            sp8c.set(vdata[tindices[i][0]].x, vdata[tindices[i][0]].y, vdata[tindices[i][0]].z);
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp74);
            
            sp8c.set(vdata[tindices[i][1]].x, vdata[tindices[i][1]].y, vdata[tindices[i][1]].z);
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp68);
            
            sp8c.set(vdata[tindices[i][2]].x, vdata[tindices[i][2]].y, vdata[tindices[i][2]].z);
            mDoMtx_stack_c::multVec(&sp8c, &sp80);
            mDoLib_project(&sp80, &sp5c);
            
            f0 = 0.5f * ((sp68.x - sp74.x) * (sp5c.y - sp74.y) - (sp68.y - sp74.y) * (sp5c.x - sp74.x));
            if (f0 > 0.0f) {
                f28 += f0;
            }
        }
    }
    
    return f28;
}

/* 800CD6D0-800CDAF8       .text draw__9dSnap_ObjFv */
void dSnap_Obj::draw() {
    if (!(field_0x1b & 1)) {
        f32 scaleX = mRadius;
        f32 scaleY = mHeight;
        mDoMtx_stack_c::copy(j3dSys.getViewMtx());
        mDoMtx_stack_c::transM(mCenter);
        mDoMtx_stack_c::scaleM(scaleX, scaleY, scaleX);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        mDoMtx_stack_c::YrotM(mAngleY);
        GXLoadPosMtxImm(mDoMtx_stack_c::get(), GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        
        GXBegin(GX_QUADS, GX_VTXFMT0, field_0x19 * 8);
        for (int i = 0; i < field_0x19; i++) {
            GXPosition3f32(cylvtx[i].x, 0.0f, cylvtx[i].z);
            GXPosition3f32(cylvtx[i].x, 1.0f, cylvtx[i].z);
            GXPosition3f32(cylvtx[i+1].x, 1.0f, cylvtx[i+1].z);
            GXPosition3f32(cylvtx[i+1].x, 0.0f, cylvtx[i+1].z);
            
            GXPosition3f32(-cylvtx[i].x, 1.0f, cylvtx[i].z);
            GXPosition3f32(-cylvtx[i].x, 0.0f, cylvtx[i].z);
            GXPosition3f32(-cylvtx[i+1].x, 0.0f, cylvtx[i+1].z);
            GXPosition3f32(-cylvtx[i+1].x, 1.0f, cylvtx[i+1].z);
        }
        
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, field_0x19 * 0xC);
        for (int i = 0; i < field_0x19; i++) {
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXPosition3f32(cylvtx[i+1].x, 1.0f, cylvtx[i+1].z);
            GXPosition3f32(cylvtx[i].x, 1.0f, cylvtx[i].z);
            
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXPosition3f32(cylvtx[i].x, 0.0f, cylvtx[i].z);
            GXPosition3f32(cylvtx[i+1].x, 0.0f, cylvtx[i+1].z);
            
            GXPosition3f32(0.0f, 1.0f, 0.0f);
            GXPosition3f32(-cylvtx[i].x, 1.0f, cylvtx[i].z);
            GXPosition3f32(-cylvtx[i+1].x, 1.0f, cylvtx[i+1].z);
            
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXPosition3f32(-cylvtx[i+1].x, 0.0f, cylvtx[i+1].z);
            GXPosition3f32(-cylvtx[i].x, 0.0f, cylvtx[i].z);
        }
    } else {
        f32 scale = mRadius;
        mDoMtx_stack_c::copy(j3dSys.getViewMtx());
        mDoMtx_stack_c::transM(mCenter);
        mDoMtx_stack_c::scaleM(scale, scale, scale);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXLoadPosMtxImm(mDoMtx_stack_c::get(), GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        
        for (int i = 0; i < 0x14; i++) {
            GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
            GXPosition3f32(vdata[tindices[i][0]].x, vdata[tindices[i][0]].y, vdata[tindices[i][0]].z);
            GXPosition3f32(vdata[tindices[i][1]].x, vdata[tindices[i][1]].y, vdata[tindices[i][1]].z);
            GXPosition3f32(vdata[tindices[i][2]].x, vdata[tindices[i][2]].y, vdata[tindices[i][2]].z);
        }
    }
}

/* 800CDAF8-800CDB2C       .text SetGeo__9dSnap_ObjFRC3Vecffs */
void dSnap_Obj::SetGeo(const Vec& center, f32 radius, f32 height, s16 angleY) {
    field_0x1b &= ~1;
    mCenter = center;
    mRadius = radius;
    mHeight = height;
    mAngleY = angleY;
}

/* 800CDB2C-800CDB68       .text SetGeoSph__9dSnap_ObjFRC3Vecf */
void dSnap_Obj::SetGeoSph(const Vec& center, f32 radius) {
    field_0x1b |= 1;
    mCenter = center;
    mRadius = radius;
    mHeight = 0.0f;
    mAngleY = 0;
}

/* 800CDB68-800CDB94       .text SetInf__9dSnap_ObjFUcPC10fopAc_ac_cUcUcs */
void dSnap_Obj::SetInf(u8 r4, const fopAc_ac_c* r5, u8 r6, u8 r7, s16 r8) {
    mPhoto = r4;
    mActorPID = fpcM_GetID(r5);
    field_0x1a = r6;
    field_0x19 = r7;
    field_0x1c = r8;
}

/* 800CDB94-800CDBB0       .text SetAreaClear__9dSnap_ObjFv */
void dSnap_Obj::SetAreaClear() {
    mMinX = 0x800;
    mMinY = 0x800;
    mMaxX = -0x800;
    mMaxY = -0x800;
}

/* 800CDBB0-800CDC04       .text SetArea__9dSnap_ObjFss */
void dSnap_Obj::SetArea(s16 x, s16 y) {
    if (GetMinX() > x) {
        mMinX = x;
    }
    if (GetMinY() > y) {
        mMinY = y;
    }
    if (GetMaxX() < x) {
        mMaxX = x;
    }
    if (GetMaxY() < y) {
        mMaxY = y;
    }
}

/* 800CDC04-800CDC18       .text ChkPhoto__9dSnap_ObjFi */
bool dSnap_Obj::ChkPhoto(int r4) {
    return mPhoto == r4 ? TRUE : FALSE;
}

/* 800CDC18-800CDC40       .text ChkSuccess__9dSnap_ObjFlf */
bool dSnap_Obj::ChkSuccess(s32 r4, f32 f1) {
    if (field_0x20 > r4 && field_0x24 > f1) {
        return true;
    }
    return false;
}

/* 800CDC40-800CDCD8       .text ChkCamCull__9dSnap_ObjCFv */
bool dSnap_Obj::ChkCamCull() const {
    if (!(field_0x1b & 1) && field_0x1c != 0x7FFF) {
        // TODO: is this VECSubtract supposed to be an inline? dSnap_Obj::GetLen?
        cXyz sp8;
        VECSubtract(&dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0))->mLookat.mEye, &mCenter, &sp8);
        s16 angle = cM_atan2s(sp8.x, sp8.z);
        if (cLib_distanceAngleS(angle, mAngleY) > field_0x1c) {
            return true;
        }
    }
    return false;
}

/* 800CDCD8-800CDCDC       .text Init__18dSnap_RegistObjElmFv */
void dSnap_RegistObjElm::Init() {}

/* 800CDCDC-800CDD70       .text Regist__18dSnap_RegistObjElmFRC9dSnap_Obj */
void dSnap_RegistObjElm::Regist(const dSnap_Obj& obj) {
    m_obj = obj;
}

/* 800CDD70-800CDD84       .text Create__12dSnap_packetFv */
void dSnap_packet::Create() {
    mFlag = 0;
    mResult = 0;
    mResultDetail = 0;
}

/* 800CDD84-800CDD94       .text ReleaseShutter__12dSnap_packetFv */
void dSnap_packet::ReleaseShutter() {
    mFlag |= 1;
}

/* 800CDD94-800CDDA0       .text ChkReleaseShutter__12dSnap_packetFv */
u32 dSnap_packet::ChkReleaseShutter() {
    return mFlag & 1;
}

/* 800CDDA0-800CDE20       .text Execute__12dSnap_packetFv */
void dSnap_packet::Execute() {
    if (ChkReleaseShutter()) {
        for (int col = 0; col < (s32)ARRAY_SIZE(m_tbl); col++) {
            m_tbl[col].Init();
            m_tbl[col].field_0x34 = 1e9f;
        }
        field_0x14 = 0;
    }
}

/* 800CDE20-800CDF98       .text Regist__12dSnap_packetFRC9dSnap_Obj */
int dSnap_packet::Regist(const dSnap_Obj& obj) {
    if (!ChkReleaseShutter()) {
        return 0;
    }
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    if (field_0x14 >= 0x3F) {
        int col;
        bool r6 = false;
        int r29;
        f32 f30 = -1e9f;
        for (col = 0; col < ARRAY_SIZE(m_tbl); col++) {
            if (f30 < m_tbl[col].field_0x34 && m_tbl[col].m_obj.GetPhoto() >= 0x48) {
                r6 = true;
                r29  = col;
                f30 = m_tbl[col].field_0x34;
            }
        }
        if (!r6) {
            return 0;
        }
        f32 dist2 = player->current.pos.abs2(obj.mCenter);
        if (obj.GetPhoto() >= 0x48 && dist2 > f30) {
            return 0;
        }
        m_tbl[r29].Regist(obj);
        m_tbl[r29].field_0x34 = dist2;
        return 0;
    } else {
        m_tbl[field_0x14].Regist(obj);
        m_tbl[field_0x14].field_0x34 = player->current.pos.abs2(m_tbl[field_0x14].m_obj.mCenter);
        field_0x14++;
        return 1;
    }
}

/* 800CDF98-800CE118       .text dSnap_MatDl__Fv */
void dSnap_MatDl() {
    GXSetNumChans(1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTexGens(0);
    GXSetNumIndStages(0);
    GXSetNumTevStages(1);
    GXSetCoPlanar(GX_FALSE);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_ZERO);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_ONE, GX_LO_CLEAR);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDither(GX_FALSE);
}

/* 800CE118-800CE298       .text dSnap_AlphaClearDL__Fv */
void dSnap_AlphaClearDL() {
    GXSetNumChans(1);
    GXSetCullMode(GX_CULL_BACK);
    GXSetNumTexGens(0);
    GXSetNumIndStages(0);
    GXSetNumTevStages(1);
    GXSetCoPlanar(GX_FALSE);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_ZERO);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    GXSetZMode(GX_FALSE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetColorUpdate(GX_FALSE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetDither(GX_TRUE);
}

/* 800CE298-800CE374       .text draw__12dSnap_packetFv */
void dSnap_packet::draw() {
    if (!ChkReleaseShutter()) {
        return;
    }
    j3dSys.reinitGX();
    ClearAlphaBuffer();
    dSnap_MatDl();
    for (int col = 0; col < field_0x14; col++) {
        GXColor color = {0xFF, 0x00, 0x00, 0xFF};
        GXSetDstAlpha(GX_TRUE, col*4);
        GXSetTevColor(GX_TEVREG0, color);
        m_tbl[col].m_obj.draw();
    }
    Judge();
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_CLEAR);
    GXSetDither(GX_TRUE);
}

/* 800CE374-800CE4A8       .text ClearAlphaBuffer__12dSnap_packetFv */
void dSnap_packet::ClearAlphaBuffer() {
    GXColor color = {0x00, 0xFF, 0x00, 0xFF};
    dSnap_AlphaClearDL();
    GXSetDstAlpha(GX_TRUE, 0xFC);
    GXSetTevColor(GX_TEVREG0, color);
    Mtx44 mtx;
    C_MTXOrtho(mtx, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 10.0f);
    GXSetProjection(mtx, GX_ORTHOGRAPHIC);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXLoadPosMtxImm(mDoMtx_getIdentity(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(0x0AE, 0x083, -0x005);
    GXPosition3s16(0x1D4, 0x083, -0x005);
    GXPosition3s16(0x1D4, 0x149, -0x005);
    GXPosition3s16(0x0AE, 0x149, -0x005);
    
    view_class* view = dComIfGp_getCamera(dComIfGp_getWindow(0)->getCameraID());
    GXSetProjection(view->mProjMtx, GX_PERSPECTIVE);
}

/* 800CE4A8-800CE610       .text Judge__12dSnap_packetFv */
void dSnap_packet::Judge() {
    if (!ChkReleaseShutter()) {
        return;
    }
    mResult = 0;
    GXDrawDone();
    GXPokeAlphaRead(GX_READ_NONE);
    for (int col = 0; col < (s32)ARRAY_SIZE(m_tbl); col++) {
        m_tbl[col].m_obj.field_0x20 = 0;
        m_tbl[col].m_obj.SetAreaClear();
    }
    for (int y = 0x56; y < 0x11C; y++) {
        for (int x = 0xAE; x < 0x1D4; x++) {
            u32 sp8;
            GXPeekARGB(x, y, &sp8);
            int r0 = sp8 >> 26;
            if (r0 >= 0x3F) {
                continue;
            }
            m_tbl[r0].m_obj.field_0x20++;
            m_tbl[r0].m_obj.SetArea(x, y);
        }
    }
    for (int col = 0; col < field_0x14; col++) {
        if (m_tbl[col].m_obj.field_0x20 == 0) {
            continue;
        }
        f32 area = m_tbl[col].m_obj.CalcArea2D();
        if (cM3d_IsZero(area)) {
            continue;
        }
        m_tbl[col].m_obj.field_0x24 = m_tbl[col].m_obj.field_0x20 / area;
    }
    SetResult();
    mFlag &= ~1;
}

/* 800CE610-800CE6A4       .text FindPhoto__12dSnap_packetFii */
int dSnap_packet::FindPhoto(int r4, int r5) {
    if (r4 < 0 || r4 >= field_0x14) {
        return -1;
    }
    for (int col = r4; col < field_0x14; col++) {
        if (m_tbl[col].m_obj.ChkPhoto(r5)) {
            return col;
        }
    }
    return -1;
}

/* 800CE6A4-800CE70C       .text JudgePost__12dSnap_packetFv */
int dSnap_packet::JudgePost() {
    int col = FindPhoto(0, 1);
    if (col == -1) {
        return 0;
    }
    if (m_tbl[col].m_obj.ChkSuccess(2000, 0.25f)) {
        return 1;
    } else {
        return 0;
    }
}

/* 800CE70C-800CE77C       .text JudgeBikutsuki__12dSnap_packetFv */
int dSnap_packet::JudgeBikutsuki() {
    int col = FindPhoto(0, 2);
    if (col == -1) {
        return 0;
    }
    if (m_tbl[col].m_obj.ChkSuccess(2000, 0.25f)) {
        return 2;
    } else {
        return 0;
    }
}

/* 800CE77C-800CE83C       .text JudgeCoupleLook__12dSnap_packetFv */
int dSnap_packet::JudgeCoupleLook() {
    int col1 = FindPhoto(0, 3);
    if (col1 == -1) {
        return 0;
    }
    int col2 = FindPhoto(col1+1, 3);
    if (col2 == -1) {
        return 0;
    }
    if (m_tbl[col1].m_obj.ChkSuccess(2000, 0.25f) &&
        m_tbl[col2].m_obj.ChkSuccess(2000, 0.25f))
    {
        return 3;
    } else {
        return 0;
    }
}

/* 800CE83C-800CE8AC       .text JudgeGF__12dSnap_packetFv */
int dSnap_packet::JudgeGF() {
    int col = FindPhoto(0, 4);
    if (col == -1) {
        return 0;
    }
    if (m_tbl[col].m_obj.ChkSuccess(5000, 0.45f)) {
        return 4;
    } else {
        return 0;
    }
}

/* 800CE8AC-800CE96C       .text JudgeGenzo__12dSnap_packetFv */
int dSnap_packet::JudgeGenzo() {
    int col1 = FindPhoto(0, 5);
    if (col1 == -1) {
        return 0;
    }
    int col2 = FindPhoto(0, 6);
    if (col2 == -1) {
        return 0;
    }
    if (m_tbl[col1].m_obj.ChkSuccess(1500, 0.2f) &&
        m_tbl[col2].m_obj.ChkSuccess(1500, 0.2f))
    {
        return 5;
    } else {
        return 0;
    }
}

/* 800CE96C-800CEA08       .text JudgeObasan4__12dSnap_packetFv */
int dSnap_packet::JudgeObasan4() {
    int col1 = FindPhoto(0, 6);
    if (col1 == -1) {
        return 0;
    }
    int col2 = FindPhoto(0, 5);
    if (col2 != -1) {
        return 0;
    }
    if (m_tbl[col1].m_obj.ChkSuccess(4000, 0.5f)) {
        return 6;
    } else {
        return 0;
    }
}

/* 800CEA08-800CEA10       .text JudgeTestM__12dSnap_packetFv */
int dSnap_packet::JudgeTestM() {
    return 0;
}

/* 800CEA10-800CEA80       .text JudgeGene__12dSnap_packetFv */
int dSnap_packet::JudgeGene() {
    int col = FindPhoto(0, field_0x10);
    if (col == -1) {
        return 0;
    }
    if (m_tbl[col].m_obj.ChkSuccess(4000, 0.5f)) {
        return field_0x10;
    } else {
        return 0;
    }
}

/* 800CEA80-800CEB80       .text JudgeFigure__12dSnap_packetFi */
int dSnap_packet::JudgeFigure(int col) {
    if (field_0x10 >= 0xD0) {
        return 0;
    }
    if (field_0x10 >= 0xCF) {
        return 0;
    }
    
    int r5;
    f32 f1;
    if (field_0x10 > 0x48) {
        int tableIndex = dSnap_PhotoIndex2TableIndex(field_0x10);
        r5 = l_CharaData[tableIndex].m0E;
        f1 = l_CharaData[tableIndex].m0A / 1000.0f;
    } else {
        return 0;
    }
    
    if (m_tbl[col].m_obj.field_0x20 < r5) {
        return 0;
    }
    
    if (m_tbl[col].m_obj.field_0x24 < f1) {
        mResultDetail |= 2;
    }
    
    if (m_tbl[col].m_obj.ChkCamCull()) {
        mResultDetail |= 1;
    }
    
    return field_0x10;
}

/* 800CEB80-800CED0C       .text SetResult__12dSnap_packetFv */
void dSnap_packet::SetResult() {
    mResult = 0;
    mResultDetail = 0;
    u8 sp8[0xB];
    for (int i = 0; i < ARRAY_SIZE(sp8); i++) {
        sp8[i] = 0;
    }
    int r30 = -1;
    for (int col = 0; col < field_0x14; col++) {
        if (m_tbl[col].m_obj.field_0x20 == 0 || m_tbl[col].m_obj.GetPhoto() == 0) {
            continue;
        }
        JUT_ASSERT(2327, 0 <= m_tbl[col].m_obj.GetPhoto() && m_tbl[col].m_obj.GetPhoto() < DSNAP_TYPE_LAST_INDEX);
        if (m_tbl[col].m_obj.GetPhoto() < (s32)ARRAY_SIZE(sp8)) {
            if (sp8[m_tbl[col].m_obj.GetPhoto()] != 0) {
                continue;
            }
            if (m_judge_tbl[m_tbl[col].m_obj.GetPhoto()] != NULL) {
                field_0x10 = m_tbl[col].m_obj.GetPhoto();
                mResult = (this->*m_judge_tbl[m_tbl[col].m_obj.GetPhoto()])();
                r30 = m_tbl[col].m_obj.field_0x20;
                if (mResult != 0) {
                    return;
                }
            }
            sp8[m_tbl[col].m_obj.GetPhoto()] = 1;
        } else {
            if (r30 < m_tbl[col].m_obj.field_0x20) {
                field_0x10 = m_tbl[col].m_obj.GetPhoto();
                mResult = JudgeFigure(col);
                r30 = m_tbl[col].m_obj.field_0x20;
            }
        }
    }
}

/* 800CED0C-800CED34       .text dSnap_Create__Fv */
void dSnap_Create() {
    l_snap.Create();
}

/* 800CED34-800CED5C       .text dSnap_ReleaseShutter__Fv */
void dSnap_ReleaseShutter() {
    l_snap.ReleaseShutter();
}

/* 800CED5C-800CED84       .text dSnap_Execute__Fv */
void dSnap_Execute() {
    l_snap.Execute();
}

/* 800CED84-800CED94       .text dSnap_GetResult__Fv */
int dSnap_GetResult() {
    return l_snap.GetResult();
}

/* 800CED94-800CEDA4       .text dSnap_GetResultDetail__Fv */
u8 dSnap_GetResultDetail() {
    return l_snap.GetResultDetail();
}

/* 800CEDA4-800CEDD0       .text dSnap_RegistSnapObj__FR9dSnap_Obj */
void dSnap_RegistSnapObj(dSnap_Obj& obj) {
    l_snap.Regist(obj);
}

/* 800CEDD0-800CEDF8       .text dSnap_RegistFig__FUcP10fopAc_ac_cfff */
void dSnap_RegistFig(u8 r3, fopAc_ac_c* actor, f32 f1, f32 f2, f32 f3) {
    dSnap_RegistFig(r3, actor, actor->current.pos, actor->shape_angle.y, f1, f2, f3);
}

/* 800CEDF8-800CEFD4       .text dSnap_RegistFig__FUcP10fopAc_ac_cRC3Vecsfff */
void dSnap_RegistFig(u8 r3, fopAc_ac_c* actor, const Vec& pos, s16 angleY, f32 f1, f32 f2, f32 f3) {
    if (!l_snap.ChkReleaseShutter()) {
        return;
    }
    if (r3 >= 0xCF) {
        return;
    }
    
    int tableIndex = dSnap_PhotoIndex2TableIndex(r3);
    const CharaData& chara = l_CharaData[tableIndex];
    mDoMtx_stack_c::YrotS(angleY);
    cXyz sp14;
    cXyz sp8;
    sp8.x = chara.offset.x;
    sp8.y = chara.offset.y;
    sp8.z = chara.offset.z;
    sp8.x = sp8.x * f3;
    sp8.y = sp8.y * f3;
    sp8.z = sp8.z * f3;
    mDoMtx_stack_c::multVec(&sp8, &sp14);
    sp14 += pos;
    
    dSnap_Obj sp20;
    sp20.SetGeo(sp14, chara.radius*f2, chara.height*f1, (int)angleY);
    sp20.SetInf(r3, actor, 0, 4, chara.m0C);
    dSnap_RegistSnapObj(sp20);
}

/* 800CEFD4-800CF054       .text dSnap_DebugDraw__Fv */
void dSnap_DebugDraw() {
    if (l_snap.ChkReleaseShutter()) {
        dComIfGd_setListMaskOff();
        j3dSys.getDrawBuffer(1)->entryImm(&l_snap, 0xFF);
        dComIfGd_setList();
    }
}

/* 800CF054-800CF058       .text dSnap_Delete__Fv */
void dSnap_Delete() {}
