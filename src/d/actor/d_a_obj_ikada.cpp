/**
 * d_a_obj_ikada.cpp
 * Object - Various Great Sea ships (Beedle, Submarines, Skull Platforms/Rafts, and Salvage Corp.)
 */

#include "d/actor/d_a_obj_ikada.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const dCcD_SrcSph daObj_Ikada_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 75.0f,
    },
};

#include "d/d_com_inf_game.h"
#include "d/res/res_ikadah.h"

#include "d/d_s_play.h"

const char daObj_Ikada_c::m_arc_name[] = "IkadaH";

const s32 daObj_Ikada_c::m_heapsize[5] = {
    0x1D00,
    0x2F60,
    0x2E20,
    0x32E0,
    0x6D60,
};

static daObj_Ikada_HIO_c l_HIO;
cXyz daObj_Ikada_c::m_rope_base_vec(0.0f, -10.0f, 0.0f); // idk probs wrong i copy pasted from d_a_ship


/* 000000EC-00000254       .text __ct__17daObj_Ikada_HIO_cFv */
daObj_Ikada_HIO_c::daObj_Ikada_HIO_c() {
    /* 0x00 */ // vtable
    mbDebugDraw = 0;
    field_0x05 = 0;
    field_0x06 = 0;
    mbNoRotAnim = 0;
    field_0x08 = 0;
    mShipOffsY_Attention = 900.0f;
    mShipOffsY_Eye = 300.0f;
    mSvWaveOffsX = -320.0f;
    mSvTrackOffsX = 240.0f;
    mTerryWaveOffsZ = 660.0f;
    mTerryWaveOffsY = 20.0f;
    mTerryTrackOffsZ = -180.0f;
    field_0x24 = 0x3C;
    mSvOffsX[0] = 265.0f;
    mSvOffsX[1] = -18.0f;
    mSvOffsX[2] = -97.0f;
    mSvOffsX[3] = -175.0f;
    mFlagScale = 0.0f;
    mFlagOffset.x = 0.0f;
    mFlagOffset.y = 0.0f;
    mFlagOffset.z = 0.0f;
    field_0x1C = 0;
    field_0x20 = 1.5f;
    field_0x1E = 100;
    field_0x28 = 100.0f;
    mTrackIndTransY = -0.04f;
    mTrackIndScaleY = 4.0f;
    mSplashScaleMax = 200.0f;
    mSplashMaxScaleTimer = 300.0f;
    mWaveVelFade = 2.0f;
    mTrackVel = 300.0f;
    mWaveVelSpeed = 2.0f;
    mWaveMaxVelocity = 15.0f;
    mWaveVelOffs = 0.0f;
    mWaveCollapsePos[0].x = -80.0f;
    mWaveCollapsePos[0].y = -50.0f;
    mWaveCollapsePos[0].z = -150.0f;
    mWaveCollapsePos[1].x = -40.0f;
    mWaveCollapsePos[1].y = -100.0f;
    mWaveCollapsePos[1].z = -350.0f;
    field_0x94 = 3000;
    mPlayerStopDistance = 6000;
    field_0x98 = 1000;
    field_0x9A = 1000;
    field_0x9C = 300.0f;
    mVelocityTargetTerry1 = 12.0f;
    mVelocityTargetTerry3 = 15.0f;
    field_0xA8 = 30.0f;
    /* Nonmatching */
}

/* 000002D8-00000324       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daObj_Ikada_c* i_this = reinterpret_cast<daObj_Ikada_c*>(model->getUserArea());
        if (i_this) {
            i_this->_nodeControl(node, model);
        }
    }
    return TRUE;
}

/* 00000324-00000458       .text _nodeControl__13daObj_Ikada_cFP7J3DNodeP8J3DModel */
void daObj_Ikada_c::_nodeControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = static_cast<J3DJoint*>(node);
    int jntNo = joint->getJntNo();
    cMtx_copy(model->getAnmMtx(jntNo), mDoMtx_stack_c::now);
    mDoMtx_stack_c::ZXYrotM(mJointRot[jntNo]);

    if(jntNo == 1) {
        mDoMtx_stack_c::XrotM(field_0x115A + field_0x115E * (g_regHIO.mChild[12].mShortRegs[5] + 5) * cM_ssin(field_0x115C));
    }

    cMtx_copy(mDoMtx_stack_c::now, J3DSys::mCurrentMtx);
    MTXCopy(mDoMtx_stack_c::now, model->getAnmMtx(jntNo));

    /* Nonmatching */
}

/* 00000458-00000494       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
void pathMove_CB(cXyz*, cXyz*, cXyz*, void*) {
    /* Nonmatching */
}

/* 00000494-000007A0       .text _pathMove__13daObj_Ikada_cFP4cXyzP4cXyzP4cXyz */
void daObj_Ikada_c::_pathMove(cXyz*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 000007A0-000007C8       .text ride_CB__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_CB(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000007C8-00000A00       .text _ride__13daObj_Ikada_cFP10fopAc_ac_c */
void daObj_Ikada_c::_ride(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000A00-00000A20       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return static_cast<daObj_Ikada_c*>(i_this)->_createHeap();
}

/* 00000A20-00000AA4       .text setCollision__13daObj_Ikada_cFv */
void daObj_Ikada_c::setCollision() {
    /* Nonmatching */
}

/* 00000AA4-00000DFC       .text checkTgHit__13daObj_Ikada_cFv */
bool daObj_Ikada_c::checkTgHit() {
    /* Nonmatching */
}

/* 00000E38-00000F04       .text pathMove__13daObj_Ikada_cFv */
void daObj_Ikada_c::pathMove() {
    /* Nonmatching */
}

/* 00000F04-00000FBC       .text HandleRight__13daObj_Ikada_cFv */
void daObj_Ikada_c::HandleRight() {
    field_0x1154 += l_HIO.field_0x20;
    J3DFrameCtrl* frameCtrl = mBckAnm.getFrameCtrl();
    if (field_0x1154 <= frameCtrl->getStart()) {
        field_0x1154 = frameCtrl->getEnd();
    }
    /* Nonmatching */
}

/* 00000FBC-00001074       .text HandleLeft__13daObj_Ikada_cFv */
void daObj_Ikada_c::HandleLeft() {
    field_0x1154 -= l_HIO.field_0x20;
    J3DFrameCtrl* frameCtrl = mBckAnm.getFrameCtrl();
    if (field_0x1154 <= frameCtrl->getStart()) {
        field_0x1154 = frameCtrl->getEnd();
    }
    /* Nonmatching */
}

/* 00001074-000012EC       .text createWave__13daObj_Ikada_cFv */
void daObj_Ikada_c::createWave() {
    static JGeometry::TVec3<f32> wave_l_direction(0.5f, 1.0f, -0.3f);
    static JGeometry::TVec3<f32> wave_r_direction(-0.5f, 1.0f, -0.3f);

    if(!mWaveLCallback.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mWavePos, &mWaveRot, NULL, 0xFF, &mWaveLCallback, -1);
        JPABaseEmitter* emitter = mWaveLCallback.getEmitter();
        if(emitter) {
            emitter->setDirection(wave_l_direction);
        }
    }

    if(!mWaveRCallback.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mWavePos, &mWaveRot, NULL, 0xFF, &mWaveRCallback, -1);
        JPABaseEmitter* emitter = mWaveRCallback.getEmitter();
        if(emitter) {
            emitter->setDirection(wave_r_direction);
        }
    }

    if (!mSplashCallBack.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0035, &mWavePos, &mWaveRot, NULL, 0xFF, &mSplashCallBack, -1);
    }

    if (!mTrackCallBack.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0036, &mTrackPos, &shape_angle, NULL, 0xFF, &mTrackCallBack, -1);
        JPABaseEmitter* emitter = mTrackCallBack.getEmitter();
        if(emitter) {
            JGeometry::TVec3<f32> scale(1.0f, 1.0f, 1.0f);
            emitter->setGlobalScale(scale);       
        }
    }
    /* Nonmatching */
}

/* 000012EC-00001528       .text setWave__13daObj_Ikada_cFv */
void daObj_Ikada_c::setWave() {
    f32 waveMaxVelocity = l_HIO.mWaveMaxVelocity;
    f32 trackVel = l_HIO.mTrackVel;
    f32 waveVelFade = l_HIO.mWaveVelFade;
    f32 target = l_HIO.mSplashScaleMax;
    if(speedF <= 2.0f) {
        waveVelFade = 0.0f;
        target = waveVelFade;
        mTrackCallBack.mState = 1;
    } else {
        createWave();
    }
    f32 temp = dLib_getWaterY(mWavePos, mObjAcch);
    mWavePos.y = temp;
    mWaveRot.y = shape_angle.y;
    f32 trackIndScaleY = l_HIO.mTrackIndScaleY;
    if (mTrackCallBack.getEmitter()) {
        f32 trackIndScaleY = l_HIO.mTrackIndScaleY;
        mTrackCallBack.setIndirectTexData(l_HIO.mTrackIndTransY, trackIndScaleY);
        mTrackCallBack.setSpeed(trackVel);
        mTrackCallBack.mBaseY = mWavePos.y;
        
        if (mObjAcch.ChkWaterHit()){
            trackVel = -1e+09;
        } else {
            trackVel = mObjAcch.m_wtr.GetHeight();
        }
        mTrackCallBack.setWaterFlatY(trackVel);
        mTrackCallBack.setLimitSpeed(3.0f);
    }
    mWaveRCallback.setSpeed(waveVelFade);
    mWaveLCallback.setSpeed(waveVelFade);
    mWaveRCallback.setMaxSpeed(waveMaxVelocity);
    mWaveLCallback.setMaxSpeed(waveMaxVelocity);

    mWaveRCallback.setPitch(l_HIO.mWaveVelOffs + 1.0f);
    mWaveLCallback.setPitch(1.0f - l_HIO.mWaveVelOffs);

    waveMaxVelocity = l_HIO.mWaveCollapsePos[0].z;
    trackVel = l_HIO.mWaveCollapsePos[0].y;
    waveVelFade = l_HIO.mWaveCollapsePos[0].x;

    cXyz anchorPos1;
    cXyz anchorPos2;

    anchorPos1.set(waveVelFade, trackVel, l_HIO.mWaveCollapsePos[0].z);
    anchorPos2.set(l_HIO.mWaveCollapsePos[1].x, l_HIO.mWaveCollapsePos[1].y, l_HIO.mWaveCollapsePos[1].z);
    mWaveRCallback.setAnchor(&anchorPos1, &anchorPos2);

    anchorPos1.x *= -1.0f;
    anchorPos2.x *= -1.0f;
    mWaveLCallback.setAnchor(&anchorPos1, &anchorPos2);

    mWaveRCallback.setMaxDisSpeed(l_HIO.mWaveVelSpeed);
    mWaveLCallback.setMaxDisSpeed(l_HIO.mWaveVelSpeed);

    // mWaveRCallback.mVelSpeed = l_HIO.mWaveVelSpeed;
    // mWaveLCallback.mVelSpeed = l_HIO.mWaveVelSpeed;
    cLib_addCalc2(&mSplashScaleTimer, target, 0.1f, 10.0f);
    mSplashCallBack.setSpeed(mSplashScaleTimer);
    mSplashCallBack.setMaxSpeed(l_HIO.mSplashMaxScaleTimer);
    /* Nonmatching */
}

/* 00001528-00001690       .text incRopeCnt__13daObj_Ikada_cFii */
void daObj_Ikada_c::incRopeCnt(int lengthChange, int minSegmentLimit) {
    int i;
    cXyz* ropeSegments = mRopeLine.getPos(0);
    int currRopeCnt = mRopeCnt;
    cXyz* currRopeSegment = &mRopeLineSegments[currRopeCnt];
    int targetRopeCnt = currRopeCnt + lengthChange;

    if (targetRopeCnt >= (int)ARRAY_SIZE(mRopeLineSegments)) {
        targetRopeCnt = ARRAY_SIZE(mRopeLineSegments);
    }
    else if (targetRopeCnt < minSegmentLimit) {
        targetRopeCnt = minSegmentLimit;
    }

    lengthChange = targetRopeCnt - currRopeCnt;

    if (lengthChange > 0) {
        cXyz ropeDisplacement = m_rope_base_vec * lengthChange;
        for (i = 0; i < mRopeCnt; i++, ropeSegments++) {
            *ropeSegments += ropeDisplacement;
        }
    }
    else {
        ropeSegments += currRopeCnt;
    }

    for (i = mRopeCnt; i < targetRopeCnt; i++, currRopeSegment++, ropeSegments++) {
        currRopeSegment->set(m_rope_base_vec);
        if (mRopeCnt) {
            ropeSegments->set(*(ropeSegments - 1) - m_rope_base_vec);
        }
    }
    mRopeCnt = (s16)targetRopeCnt;
    /* Nonmatching */
}

/* 00001690-00001DEC       .text setRopePos__13daObj_Ikada_cFv */
void daObj_Ikada_c::setRopePos() {
    /* Nonmatching */
}

/* 00001DEC-000024A4       .text setMtx__13daObj_Ikada_cFv */
void daObj_Ikada_c::setMtx() {
    dLib_waveRot(&current.pos, 0.0f, &mWave);
    int temp = mLinkRideRockAmpl * (g_regHIO.mChild[12].mShortRegs[5] + 10) * cM_ssin(mLinkRideRockTimer);

    // u32 temp2 = temp ^ 0x80000000;
    // local_68 = 0x43300000;

    // s16 val = g_regHIO.mChild[8].mShortRegs[5];
    // int temp6 = val + 0xC8;
    // int waveAnim1X = temp6 * cM_ssin(mWaveAnimTimer);

    int waveAnim1X = (g_regHIO.mChild[8].mShortRegs[5] + 0xC8) * cM_ssin(mWaveAnimTimer);
    int waveAnim1Z = (g_regHIO.mChild[8].mShortRegs[6] + 0x3C) * cM_ssin(mWaveAnimTimer);
    s16 plyAngleY = fopAcM_searchPlayerAngleY(this);

    s16 angleY = temp* cM_ssin(shape_angle.y + plyAngleY);
    int waveAnim2X = cM_scos(angleY);
    int waveAnim2Z = cM_ssin(angleY);
    if (l_HIO.mbNoRotAnim == 0) {
        shape_angle.x = mWave.mRotX + waveAnim2X + waveAnim1X;
        shape_angle.z = mWave.mRotZ + waveAnim2Z + waveAnim1Z;
    }
    mpModel->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);

    if(isCrane()){
        mDoMtx_stack_c::transM(0.0f, 30.0f, -260.0f);
    }
    // cMtx_copy(mpModel->getBaseTRMtx(), mDoMtx_stack_c::now);

    mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());

    if(isCrane()){
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::YrotM(0x4000);
        cXyz temp2;
        fopAc_ac_c* pSv;

        for (int i = 0; i < 4; i++) {
            temp2.x = l_HIO.mSvOffsX[i];

            if (fopAcM_SearchByID(mSvId[i], &pSv)) {
                cMtx_multVec(mDoMtx_stack_c::get(), &temp2, &pSv->current.pos);

            }
        }

        cXyz temp3;
        temp3.x = l_HIO.mSvWaveOffsX;

        mDoMtx_stack_c::multVec(&temp3, &mWavePos);
        temp3.x = l_HIO.mSvTrackOffsX;
        mDoMtx_stack_c::multVec(&temp3, &mTrackPos);

    }

    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);

    if(isBonbori()){
        mLightRotY += 0xd0;
        mLightRotX+=  0x100;

        cXyz temp2(
            g_regHIO.mChild[0xc].mFloatRegs[2],
            g_regHIO.mChild[0xc].mFloatRegs[3] + 340.0f,
            g_regHIO.mChild[0xc].mFloatRegs[4] + 200.0f
        );

        mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
        mDoMtx_stack_c::multVec(&temp2, &mFirePos);
        mDoMtx_stack_c::transM(temp2);
        mDoMtx_stack_c::YrotM(mLightRotY);
        mDoMtx_stack_c::XrotM(mLightRotX);

        mDoMtx_stack_c::scaleM(mLightPower, mLightPower, mLightPower);
        mDoMtx_copy(mDoMtx_stack_c::get(), mLightMtx);

        mPLight.mPos.x = mDoMtx_stack_c::now[0][3];
        mPLight.mPos.y = mDoMtx_stack_c::now[1][3];
        mPLight.mPos.z = mDoMtx_stack_c::now[2][3];
        mPLight.mColor.r = 600;
        mPLight.mColor.g = 400;
        mPLight.mColor.b = 0x78;
        mPLight.mFluctuation = 250.0f;
    }

    if(isBonbori()){ // order is differnet in check in ghidra??? 
        cXyz temp2(
            g_regHIO.mChild[0xc].mFloatRegs[2] - 150.0f,
            g_regHIO.mChild[0xc].mFloatRegs[3] + 380.0f,
            g_regHIO.mChild[0xc].mFloatRegs[4] + 40.0f
        );
        mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
        mDoMtx_stack_c::multVec(&temp2, &mSePos);
    }

    if(isCrane() || isBonbori()) {

        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);

        cXyz temp2;


        temp2.y = l_HIO.mShipOffsY_Attention;

        mDoMtx_stack_c::multVec(&temp2, &attention_info.position);

        temp2.y = l_HIO.mShipOffsY_Eye;
        mDoMtx_stack_c::multVec(&temp2, &eyePos);

        if (!isCrane()) {
            f32 temp3 = 5.0f + g_regHIO.mChild[8].mFloatRegs[5];
            if (mCurMode == 10) {
                temp3 = 20.0f;
            }
            temp2.z = l_HIO.mTerryWaveOffsZ + temp3;
            temp2.y = l_HIO.mTerryWaveOffsY;
            mDoMtx_stack_c::multVec(&temp2, &mWavePos);

            temp2.z = l_HIO.mTerryTrackOffsZ;
            temp2.y = 0.0f;
            mDoMtx_stack_c::multVec(&temp2, &mTrackPos);
        }
    }
    /* Nonmatching */
}

/* 000024A4-000027A4       .text modeProc__13daObj_Ikada_cFQ213daObj_Ikada_c6Proc_ei */
void daObj_Ikada_c::modeProc(daObj_Ikada_c::Proc_e proc, int newMode) {

    typedef void(daObj_Ikada_c::*daObj_Ikada_mode_t)(void);
    struct mode_entry_t {
        daObj_Ikada_mode_t init;
        daObj_Ikada_mode_t exec;
        const char* name;
    };

    static mode_entry_t mode_tbl[] = {
        {
            &daObj_Ikada_c::modeWaitInit,
            &daObj_Ikada_c::modeWait,
            "WAIT"
        },
        {
            &daObj_Ikada_c::modeCraneUpInit,
            &daObj_Ikada_c::modeCraneUp,
            "CRANE_UP"
        },
        {
            &daObj_Ikada_c::modeCraneUpWaitInit,
            &daObj_Ikada_c::modeCraneUpWait,
            "CRANE_UP_WAIT"
        },
        {
            &daObj_Ikada_c::modeCraneDownInit,
            &daObj_Ikada_c::modeCraneDown,
            "CRANE_DOWN"
        },
        {
            &daObj_Ikada_c::modeCraneDownWaitInit,
            &daObj_Ikada_c::modeCraneDownWait,
            "CRANE_DOWN_WAIT"
        },
        {
            &daObj_Ikada_c::modeCraneTurnInit,
            &daObj_Ikada_c::modeCraneTurn,
            "CRANE_TURN"
        },
        {
            &daObj_Ikada_c::modeCraneResetInit,
            &daObj_Ikada_c::modeCraneReset,
            "CRANE_RESET"
        },
        {
            &daObj_Ikada_c::modeCraneWaitInit,
            &daObj_Ikada_c::modeCraneWait,
            "CRANE_WAIT"
        },
        {
            &daObj_Ikada_c::modePathMoveInit,
            &daObj_Ikada_c::modePathMove,
            "PATH_MOVE"
        },
        {
            &daObj_Ikada_c::modeStopInit,
            &daObj_Ikada_c::modeStop,
            "STOP"
        },
        {
            &daObj_Ikada_c::modePathMoveTerryInit,
            &daObj_Ikada_c::modePathMoveTerry,
            "PATH_MOVE_TERRY"
        },
        {
            &daObj_Ikada_c::modeStopTerryInit,
            &daObj_Ikada_c::modeStopTerry,
            "STOP_TERRY"
        },
        {
            &daObj_Ikada_c::modeStopBombTerryInit,
            &daObj_Ikada_c::modeStopBombTerry,
            "STOP_BOMB_TERRY"
        },
    };

    if (proc == PROC_INIT) {
        mCurMode = newMode;
        (this->*mode_tbl[mCurMode].init)();
    }
    else if (proc == PROC_EXEC) {
        (this->*mode_tbl[mCurMode].exec)();
    }
    /* Nonmatching */
}

/* 000027A4-000027A8       .text modeWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeWaitInit() {
    /* Nonmatching */
}

/* 000027A8-00002840       .text modeWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeWait() {
    if (isCrane()) {
        if (l_HIO.field_0x1C != 0) {
            if (l_HIO.field_0x1C > mRopeCnt) {
                incRopeCnt(-1, 0);
            } else if (mRopeCnt < l_HIO.field_0x1C) {
                incRopeCnt(1, 0);
            }
        }
        if (g_regHIO.mChild[12].mShortRegs[4] != 0) {
            modeProcInit(1);
        }
    }
    /* Nonmatching */
}

/* 00002840-00002844       .text modeCraneUpInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpInit() {
    /* Nonmatching */
}

/* 00002844-0000289C       .text modeCraneUp__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUp() {
    if (mRopeCnt > 15) {
        HandleRight();
        incRopeCnt(-1, 0);
    } else {
        modeProcInit(2);
    }
}

/* 0000289C-000028B0       .text modeCraneUpWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpWaitInit() {
    mTimer = (int)l_HIO.field_0x24;
    /* Nonmatching */
}

/* 000028B0-000028F8       .text modeCraneUpWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpWait() {
    if(cLib_calcTimer(&mTimer) == 0){
        modeProcInit(6);
    }
}

/* 000028F8-00002904       .text modeCraneDownInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownInit() {
    field_0x115E = 0x96;
}

/* 00002904-000029B0       .text modeCraneDown__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDown() {
    cLib_addCalcAngleS2(&field_0x115E, 0, 10, 10);
    if (field_0x115E < 20) {
        HandleLeft();
        if (mRopeCnt < l_HIO.field_0x1E) {
            incRopeCnt(1, 0);
        }
        else {
            modeProcInit(7);
        }
    }
    else {
        field_0x115C += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
    }
  return;
    cLib_addCalcAngleS2(&field_0x115E, 0, 10, 10);
    if (field_0x115E < 20) {
        HandleRight();
        if (field_0x1168 == 1) {
            field_0x1158 = 0x4000;
        }
        else {
            field_0x1158 = -0x4000;
        }
        cLib_addCalcAngleS2(&field_0x115A, field_0x1158, 10, 0x100);
        if (cLib_distanceAngleS(field_0x115A, field_0x1158) <= 0x100) {
            modeProcInit(4);
        }
    }
    else {
        field_0x115C += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
    }
    /* Nonmatching */
}

/* 000029B0-000029C4       .text modeCraneDownWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownWaitInit() {
    mTimer = l_HIO.field_0x24;
    /* Nonmatching */
}

/* 000029C4-00002A0C       .text modeCraneDownWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownWait() {
    if(cLib_calcTimer(&mTimer) == 0){
        modeProcInit(3);
    }
}

/* 00002A0C-00002A24       .text modeCraneTurnInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneTurnInit() {
    field_0x115E = 150;
    speedF = 0.0f;
    /* Nonmatching */
}

/* 00002A24-00002AEC       .text modeCraneTurn__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneTurn() {
    cLib_addCalcAngleS2(&field_0x115E, 0, 10, 10);
    if (field_0x115E < 20) {
        HandleRight();
        if (field_0x1168 == 1) {
            field_0x1158 = 0x4000;
        }
        else {
            field_0x1158 = -0x4000;
        }
        cLib_addCalcAngleS2(&field_0x115A, field_0x1158, 10, 0x100);
        if (cLib_distanceAngleS(field_0x115A, field_0x1158) <= 0x100) {
            modeProcInit(4);
        }
    }
    else {
        field_0x115C += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
    }
}

/* 00002AEC-00002B04       .text modeCraneResetInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneResetInit() {
    field_0x115E = 0x96;
    speedF = 0.0f;
    /* Nonmatching */
}

/* 00002B04-00002BB4       .text modeCraneReset__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneReset() {
    cLib_addCalcAngleS2(&field_0x115E, 0, 10, 10);
    if (field_0x115E < 20) {
        HandleLeft();
        field_0x1158 = 0;
        cLib_addCalcAngleS2(&field_0x115A, field_0x1158, 10, 0x100);
        if (cLib_distanceAngleS(field_0x115A, field_0x1158) <= 0x100) {
            modeProcInit(8);
        }
    }
    else {
        field_0x115C += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
    }
}

/* 00002BB4-00002BC0       .text modeCraneWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneWaitInit() {
    mTimer = 600;
}

/* 00002BC0-00002C08       .text modeCraneWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneWait() {
    if (!cLib_calcTimer(&mTimer)) {
        modeProcInit(1);
    }
}

/* 00002C08-00002C60       .text modePathMoveInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveInit() {
    /* Nonmatching */
}

/* 00002C60-00002DC0       .text modePathMove__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMove() {
    if (l_HIO.field_0x06 != 0) {
        HandleRight();
    }
    if (l_HIO.field_0x05 != 0) {
        HandleLeft();
    }

    if (l_HIO.field_0x08 == 0 && mPathId != 0xFF) {
        if (mbCraneMode == 0) {
            f32 temp2 = (mCurPathP1 - current.pos).absXZ();
            if (temp2 < 50.0f) {
                mVelocityFwdTarget = 8.0f;
            } else {
                mVelocityFwdTarget = 1.0f;
            }
        } else {
            mVelocityFwdTarget = 8.0f;
            
        }
        pathMove();
    }
    /* Nonmatching */
}

/* 00002DC0-00002DC4       .text modeStopInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopInit() {
}

/* 00002DC4-00002F04       .text modeStop__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStop() {
    /* Nonmatching */
}

/* 00002F04-00002F10       .text modePathMoveTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveTerryInit() {
    /* Nonmatching */
}

/* 00002F10-00003228       .text modePathMoveTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveTerry() {
    bool temp;
    f32 dist;

    setCollision();
    if (checkTgHit() == false) {
        temp = false;
        dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
        if (dist < l_HIO.mPlayerStopDistance && !cLib_calcTimer(&mStopTimer)) {
            f32 temp2 = cM_rndF(120.0f);
            mStopTimer = (int)(temp2 + 240.0f);
            temp2 = cM_rndF(100.0f);
            if (temp2 < 50.0f) {
                mDoAud_seStart(JA_SE_OBJ_BS_MELODY_2, &mSePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            } else {
                mDoAud_seStart(JA_SE_OBJ_BS_MELODY_1, &mSePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            }
        }
        if (mType == 1) {
            mVelocityFwdTarget = l_HIO.mVelocityTargetTerry1;
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if (dist < l_HIO.field_0x9A) {
                    temp = true;
                }
            }
            else if (dist < l_HIO.field_0x94) {
                temp = true;
            }
        } else if (this->mType == 3) {
            mVelocityFwdTarget = l_HIO.mVelocityTargetTerry3;
            if (dist < l_HIO.mPlayerStopDistance) {
                mVelocityFwdTarget = l_HIO.field_0xA8;
            }
            if (dist < l_HIO.field_0x98) {
                temp = true;
            }
        }

        if (mbIsLinkRiding) {
            mTimer = 30;
        } else {
            if (!cLib_calcTimer(&mTimer) && temp) {
                modeProcInit(0xB);
                return;
            }
        }

        mLinkRideRockTimer += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
        cLib_addCalcAngleS2(&mLinkRideRockAmpl, 0, 10, 10);

        if (mLinkRideRockAmpl <= 0xa) {
            mLinkRideRockAmpl = 0;
        }

        if (mPathId != 0xff) {
            pathMove();
        }
    }
    /* Nonmatching */
}

/* 00003228-00003234       .text modeStopTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopTerryInit() {
    mTimer = 210;
}

/* 00003234-0000342C       .text modeStopTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopTerry() {
    bool temp;
    f32 dist;

    setCollision();
    if (checkTgHit() == false) {
        temp = false;
        dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));

        if(mType == 1) {
            if(dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if(l_HIO.field_0x9A <= dist) {
                    temp = true;
                }
            } else if(l_HIO.field_0x94 <= dist){
                temp = true;
            }
        } else if(mType == 3 && l_HIO.field_0x98 <= dist) {
            temp = true;
        }

        if (temp) {
            modeProcInit(10);
        } else {
            if (mbIsLinkRiding) {
                if(!cLib_calcTimer(&mTimer)) {
                    modeProcInit(10);
                    return;
                }
            } else {
                mTimer = 300;

            }

            mLinkRideRockTimer += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
            cLib_addCalcAngleS2(&mLinkRideRockAmpl, 0, 10, 10);

            if (mLinkRideRockAmpl <= 0xa) {
                mLinkRideRockAmpl = 0;
            }

            mVelocityFwdTarget = 0.0f;
            if (mPathId != 0xff) {
                pathMove();
            }
        }
    }
    /* Nonmatching */
}

/* 0000342C-00003430       .text modeStopBombTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopBombTerryInit() {
}

/* 00003430-000034D0       .text modeStopBombTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopBombTerry() {
    setCollision();
    if (checkTgHit() == false) {
        mLinkRideRockTimer += g_regHIO.mChild[12].mShortRegs[2] + 0x1830;
        cLib_addCalcAngleS2(&mLinkRideRockAmpl, 0, 10, 10);

        if (mLinkRideRockAmpl <= 0xA) {
            mLinkRideRockAmpl = 0;
        }
        mVelocityFwdTarget = 0.0f;
        if (mPathId != 0xff) {
            pathMove();
        }
    }
    /* Nonmatching */
}

/* 000034D0-00003750       .text epProc__13daObj_Ikada_cFv */
void daObj_Ikada_c::epProc() {
    if(!dKy_daynight_check()){
        mFireParticle.end();
        mPLight.mPower = 0.0f;
    } else {
        if(!mFireParticle.getEmitter()) {
            static cXyz fire_scale(0.5f, 0.5f, 0.5f);

            fire_scale.x = g_regHIO.mChild[12].mFloatRegs[10];
            dComIfGp_particle_set(dPa_name::ID_COMMON_01EA, &mFirePos, NULL, &fire_scale, 0xFF, &mFireParticle, -1);

        }

        if(!mFireParticle.getEmitter()) {
  

            dComIfGp_particle_setSimple(dPa_name::ID_COMMON_4004, &cXyz(
                current.pos.x,
                current.pos.z,
                current.pos.y + 20.0f
            ));
            f32 temp2;

            if (cLib_calcTimer(&mEpTimer0) == 0) {
                temp2 = cM_rndF(g_regHIO.mChild[0].mFloatRegs[2] + 5.0f);
                mEpTimer0 = g_regHIO.mChild[0].mFloatRegs[2] + temp2;
                temp2 = cM_rndF(g_regHIO.mChild[0].mFloatRegs[6] + 4.0f);
                field_0x050C = g_regHIO.mChild[0].mFloatRegs[7] + temp2 + 8.0f;
            }

            if (cLib_calcTimer(&mEpTimer1) == 0) {
                temp2 = cM_rndF(6.0f);
                mEpTimer1 = (s16)(temp2 + 3.0f);
                temp2 = cM_rndF(0.075f);
                mLightPowerTarget = temp2 + 0.75f;
            }
            cLib_addCalc2(&field_0x0508, field_0x050C, 1.0f, g_regHIO.mChild[0].mFloatRegs[4] + 0.1f + 0.9f);
            cLib_addCalc2(&mLightPower, mLightPowerTarget, 0.4f, 0.04f);
            mPLight.mPower = mLightPower * 150.0f;
        }     // no local18?
    }
    /* Nonmatching */
}

/* 00003750-00003CA0       .text _execute__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_execute() {
    JGeometry::TVec3<f32> scale(3.0f, 3.0f, 3.0f);
    mWaveAnimTimer = g_regHIO.mChild[8].mShortRegs[4] + mWaveAnimTimer + 0x200;
    f32 temp = 5.0f;
    if (mCurMode == 10) {
        temp = 20.0f;
    }
    temp += g_regHIO.mChild[8].mFloatRegs[5];
    f32 temp2 = cM_ssin(mWaveAnimTimer);

    if (mBombSmokeEasterEgg.getEmitter() != NULL) {
        mBombSmokeRot.x = shape_angle.x;
        mBombSmokeRot.y = shape_angle.y;
        mBombSmokeRot.z = shape_angle.z;
        mBombSmokeRot.y += mBombSmokeAngle;
        mBombSmokeEasterEgg.getEmitter()->setGlobalScale(scale);
        // globalscale2d?
        mBombSmokePos = current.pos;
        mBombSmokePos.y = l_HIO.field_0x28;
        if(cLib_calcTimer(&field_0x04A8)){
            mBombSmokeEasterEgg.remove();
        }
    }
    if (field_0x1166 == 1 && mCurMode != 9) {
        field_0x02F4 = mCurMode;
        // modeProc(0, 9);
    }

    if (isBonbori()) {
        epProc();
    }

    if (isCrane()) {
        setRopePos();
    }

    if(isCrane()) {
        //local_28 = CONCAT44(0x43300000,(int)this->field125_0x1154 ^ 0x80000000);
        mBckAnm.setFrame((int)field_0x1154);
        if (g_regHIO.mChild[12].mShortRegs[0] != 0) {
            mJointRot[g_regHIO.mChild[12].mShortRegs[0]].x = g_regHIO.mChild[12].mShortRegs[1];
            mJointRot[g_regHIO.mChild[12].mShortRegs[0]].x = g_regHIO.mChild[12].mShortRegs[2];
            mJointRot[g_regHIO.mChild[12].mShortRegs[0]].x = g_regHIO.mChild[12].mShortRegs[3];
        }
    }
    // modeProc(this,1,0xd);
    current.pos.y = temp * temp2 + dLib_getWaterY(current.pos, mObjAcch);
    setMtx();
    mpModel->calc();
    if (isCrane() || isBonbori()) {
        temp = scale.x;
        temp2 = temp * 1000.0f;
        // s32 temp3 = fopAcM_checkCullingBox(
        //     mpModel->getBaseTRMtx(), temp * -1000.0f, temp * -50.0f, 
        //     temp * -1000.0f, temp2, temp2, temp2
        // );
        if(speedF <= 2.0f ||
            fopAcM_checkCullingBox(
            mpModel->getBaseTRMtx(), temp * -1000.0f, temp * -50.0f, 
            temp * -1000.0f, temp2, temp2, temp2
            ) & 0xff != 0 || 
            fopAcM_searchPlayerDistanceXZ(dComIfGp_getPlayer(0)) > 18000.0f
        ) {
            mWaveRCallback.remove();
            mWaveLCallback.remove();
            mSplashCallBack.remove();

            mTrackCallBack.mState = 1;
        } else {
            setWave();
        }
    }
    if(isFlag()) {
        fopAc_ac_c* actor = fopAcM_SearchByID(mFlagPcId);
        if(actor != NULL) {
            //  waveCollapsePos1Y[4].parent.parent.mDtTg.parent.mpTagData = (create_request *)&this->mMtx; 
            if (l_HIO.mFlagOffset.x != 0.0f || l_HIO.mFlagOffset.y != 0.0f || l_HIO.mFlagOffset.z != 0.0f) {
                mFlagOffset.x = l_HIO.mFlagOffset.x;
                mFlagOffset.y = l_HIO.mFlagOffset.y;
                mFlagOffset.z = l_HIO.mFlagOffset.z;
            }
            if (l_HIO.mFlagScale != 0.0f) {
                mFlagScale = l_HIO.mFlagScale;
            }
            // maybe actor setbasescale
            //  waveCollapsePos1Y[4].parent.parent.mLyTg.parent.parent.mpNextNode = (node_class *)this->mFlagScale;
            // *(cXyz **)&  waveCollapsePos1Y[4].parent.parent.mDtTg.parent.mbAdded = &this->mFlagOffset;
        }
        
    }
    mbIsLinkRiding = 0;
    if (isBonbori()) {
        f32 temp = (current.pos - old.pos).absXZ();

        // temp = temp / 30.0f;
        // temp2 = 0.0f;
        // if ((temp > 0.0f) && (temp2 = temp, temp >= 1.0f)) {
        //     temp2 = 1.0f;
        // }
        mDoAud_seStart(JA_SE_OBJ_BS_BOAT_CRUISE, &eyePos, temp2 * 100.0f, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    }
    return false;
    /* Nonmatching */
}

/* 00003CA0-00003CD4       .text debugDraw__13daObj_Ikada_cFv */
void daObj_Ikada_c::debugDraw() {
    /* Nonmatching */
}

/* 00003CD4-00003EE0       .text _draw__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_draw() {
    /* Nonmatching */
}

/* 00003EE0-00003F34       .text getArg__13daObj_Ikada_cFv */
void daObj_Ikada_c::getArg() {
    u32 param = fopAcM_GetParam(this);
    s16 homeAngleX = home.angle.x;
    mType = param & 0xf;
    if (mType != 4) {
        field_0x0294 = fopAcM_GetParamBit(param, 4, 8) & 0x3f;
        field_0x0298 = fopAcM_GetParamBit(param, 10, 8) & 0xff;
        field_0x02A0 = fopAcM_GetParamBit(param, 0x12, 8) & 0xff;
        field_0x029C = homeAngleX & 0xff;
        mPathId = fopAcM_GetParamBit(homeAngleX, 8, 8);
        return;
    }
    mPathId = param >> 0x10;
}

/* 00003F34-00004838       .text createInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::createInit() {
    mInitPos = current.pos;
    f32 temp = cM_rndF(120.0f);
    f32 temp2 = temp + 240.f;
    mStopTimer = temp2;
    if(mType = 1 || mType == 2 || mType == 3) {
       
    }
    /* Nonmatching */
}

/* 00004838-00004B60       .text _createHeap__13daObj_Ikada_cFv */
BOOL daObj_Ikada_c::_createHeap() {
    static const u32 dzb[] = {
        IKADAH_DZB_VIKAE,
        IKADAH_DZB_VTSP,
        IKADAH_DZB_VIKAH,
        IKADAH_DZB_VTSP,
        IKADAH_DZB_VSVSP
    };

    static const u32 bdl[] = {
        IKADAH_BDL_VIKAE,
        IKADAH_BDL_VTSP,
        IKADAH_BDL_VIKAH,
        IKADAH_BDL_VTSP2,
        IKADAH_BDL_VSVSP
    };

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, bdl[mType]);
    JUT_ASSERT(0x87A, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if(mpModel == NULL) {
        return FALSE;
    }
    if (isCrane()) {
        J3DAnmTransform * bck = (J3DAnmTransform *)dComIfG_getObjectRes(m_arc_name, IKADAH_BCK_SVSHIP_KAITEN);
        JUT_ASSERT(0x884, bck != NULL);

        if (!mBckAnm.init(modelData, bck, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false)){
            return FALSE;
        }
    }
    mpModel->setUserArea((u32)this);

    if (isCrane()) {
        for(int i = 0; i < modelData->getJointNum(); i++) {
            if(i < 4 && i != 0){
                modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
            }
        }
    }

    setMtx();
    mpBgW = new dBgW();
    if(mpBgW == NULL) {
        return FALSE;
    }

    cBgD_t* pData = (cBgD_t *)dComIfG_getObjectRes(m_arc_name, dzb[mType]);
    if((mpBgW->Set(pData, dBgW::MOVE_BG_e, &mMtx) && 0xff) == 1){
        return FALSE;
    }

    if(isCrane()) {
        if (mRopeLine.init(1, 200, (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE), 0) == 0) {
            return FALSE;
        }

        modelData = (J3DModelData*)dComIfG_getObjectRes("Link", 0x2E);
        JUT_ASSERT(0x8B4, modelData != NULL);
        mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x1100002);
        if (mpModel == NULL) {
            return FALSE;
        }
    }
    return TRUE;
    /* Nonmatching */
}

/* 00004B60-00004C18       .text _create__13daObj_Ikada_cFv */
cPhs_State daObj_Ikada_c::_create() {
    fopAcM_SetupActor(this, daObj_Ikada_c);
    cPhs_State phase = dComIfG_resLoad(&mPhs, m_arc_name);
  
    if (phase == cPhs_COMPLEATE_e) {
        getArg();
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize[mType])) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    return phase;
}

/* 00005320-0000543C       .text _delete__13daObj_Ikada_cFv */
BOOL daObj_Ikada_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    mWaveRCallback.remove();
    mWaveLCallback.remove();
    mSplashCallBack.remove();
    mTrackCallBack.remove();
    mRippleCallBack.end();
    mFireParticle.end();
    mBombSmokeEasterEgg.end();

    mDoAud_seDeleteObject(&mSePos);
    

    if (isBonbori()) {
        dKy_plight_cut(&mPLight);
    }
    
    if (heap != NULL && mpBgW != NULL) {
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        } 
    }
    return TRUE;
}

/* 0000543C-0000545C       .text daObj_IkadaCreate__FPv */
static s32 daObj_IkadaCreate(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_create();
}

/* 0000545C-00005480       .text daObj_IkadaDelete__FPv */
static BOOL daObj_IkadaDelete(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_delete();
}

/* 00005480-000054A4       .text daObj_IkadaExecute__FPv */
static BOOL daObj_IkadaExecute(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_execute();
}

/* 000054A4-000054C8       .text daObj_IkadaDraw__FPv */
static BOOL daObj_IkadaDraw(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_draw();
}

/* 000054C8-000054D0       .text daObj_IkadaIsDelete__FPv */
static BOOL daObj_IkadaIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_IkadaMethodTable = {
    (process_method_func)daObj_IkadaCreate,
    (process_method_func)daObj_IkadaDelete,
    (process_method_func)daObj_IkadaExecute,
    (process_method_func)daObj_IkadaIsDelete,
    (process_method_func)daObj_IkadaDraw,
};

actor_process_profile_definition g_profile_OBJ_IKADA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_IKADA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Ikada_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_IKADA,
    /* Actor SubMtd */ &daObj_IkadaMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
