#ifndef D_A_BK_H
#define D_A_BK_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_hostIO.h"

class dPath;
namespace daObj_Search { class Act_c; };

class bk_class : public fopEn_enemy_c {
public:
    /* 0x02AC */ request_of_phase_process_class mPhase;
    /* 0x02B4 */ u8 mType;
    /* 0x02B5 */ u8 m02B5;
    /* 0x02B6 */ u8 m02B6;
    /* 0x02B7 */ u8 m02B7;
    /* 0x02B8 */ u8 m02B8;
    /* 0x02B9 */ u8 m02B9;
    /* 0x02BA */ u8 m02BA;
    /* 0x02BB */ u8 m02BB[0x02BC - 0x02BB];
    /* 0x02BC */ mDoExt_McaMorf* mpMorf;
    /* 0x02C0 */ u8 m02C0[0x02C4 - 0x02C0];
    /* 0x02C4 */ mDoExt_btpAnm* m02C4;
    /* 0x02C8 */ s16 m02C8;
    /* 0x02CA */ s16 m02CA;
    /* 0x02CC */ s16 m02CC;
    /* 0x02CE */ s8 m02CE;
    /* 0x02CF */ u8 m02CF[0x02D0 - 0x02CF];
    /* 0x02D0 */ J3DModel* m02D0;
    /* 0x02D4 */ u8 m02D4;
    /* 0x02D5 */ u8 m02D5;
    /* 0x02D6 */ u8 m02D6[0x02D8 - 0x02D6];
    /* 0x02D8 */ J3DModel* m02D8;
    /* 0x02DC */ u8 m02DC;
    /* 0x02DD */ u8 m02DD;
    /* 0x02DE */ s8 m02DE;
    /* 0x02DF */ u8 m02DF[0x02E0 - 0x02DF];
    /* 0x02E0 */ u32 mShadowId;
    /* 0x02E4 */ u8 m02E4[0x02E8 - 0x02E4];
    /* 0x02E8 */ J3DModel* m02E8;
    /* 0x02EC */ f32 m02EC;
    /* 0x02F0 */ int m02F0;
    /* 0x02F4 */ int m02F4;
    /* 0x02F8 */ int m02F8;
    /* 0x02FC */ int m02FC;
    /* 0x0300 */ s16 m0300[5];
    /* 0x030A */ s16 m030A;
    /* 0x030C */ s16 m030C;
    /* 0x030E */ s16 m030E;
    /* 0x0310 */ s16 m0310;
    /* 0x0312 */ u8 m0312[0x0314 - 0x0312];
    /* 0x0314 */ s16 m0314;
    /* 0x0316 */ s16 m0316;
    /* 0x0318 */ u8 m0318;
    /* 0x031C */ f32 mPlayerDistance;
    /* 0x0320 */ cXyz m0320;
    /* 0x032C */ u8 m032C[0x0330 - 0x032C];
    /* 0x0330 */ s16 m0330;
    /* 0x0332 */ s16 m0332;
    /* 0x0334 */ s16 m0334;
    /* 0x0336 */ s16 m0336;
    /* 0x0338 */ cXyz m0338;
    /* 0x0344 */ csXyz m0344;
    /* 0x034A */ s16 m034A;
    /* 0x034C */ s16 m034C;
    /* 0x034E */ u8 m034E;
    /* 0x034F */ u8 m034F;
    /* 0x0350 */ dPa_smokeEcallBack m0350;
    /* 0x0370 */ damagereaction dr;
    /* 0x0B2C */ u8 m0B2C[0x0B30 - 0x0B2C];
    /* 0x0B30 */ int m0B30;
    /* 0x0B34 */ int m0B34;
    /* 0x0B38 */ u8 m0B38[0x0B44 - 0x0B38];
    /* 0x0B44 */ cXyz m0B44[2];
    /* 0x0B5C */ int m0B5C;
    /* 0x0B60 */ int m0B60;
    /* 0x0B64 */ f32 m0B64;
    /* 0x0B68 */ f32 m0B68;
    /* 0x0B6C */ f32 m0B6C;
    /* 0x0B70 */ f32 m0B70;
    /* 0x0B74 */ f32 m0B74;
    /* 0x0B78 */ s16 m0B78;
    /* 0x0B7A */ s8 m0B7A;
    /* 0x0B7B */ s8 m0B7B;
    /* 0x0B7C */ u8 m0B7C[0x0B88 - 0x0B7C];
    /* 0x0B88 */ dCcD_Cyl m0B88;
    /* 0x0CB8 */ dCcD_Cyl m0CB8;
    /* 0x0DE8 */ dCcD_Sph m0DE8;
    /* 0x0F14 */ dCcD_Sph m0F14;
    /* 0x1040 */ dCcD_Sph m1040;
    /* 0x116C */ cXyz m116C;
    /* 0x1178 */ cXyz m1178;
    /* 0x1184 */ u8 m1184[0x1190 - 0x1184];
    /* 0x1190 */ cXyz m1190;
    /* 0x119C */ cXyz m119C;
    /* 0x11A8 */ cXyz m11A8;
    /* 0x11B4 */ u8 m11B4[0x11C0 - 0x11B4];
    /* 0x11C0 */ cXyz m11C0;
    /* 0x11CC */ cXyz m11CC;
    /* 0x11D8 */ u8 m11D8[0x11E4 - 0x11D8];
    /* 0x11E4 */ cXyz m11E4;
    /* 0x11F0 */ u8 m11F0;
    /* 0x11F1 */ u8 m11F1;
    /* 0x11F2 */ u8 m11F2;
    /* 0x11F3 */ u8 m11F3;
    /* 0x11F4 */ s16 m11F4;
    /* 0x11F8 */ fopAc_ac_c* m11F8;
    /* 0x11FC */ u32 m11FC;
    /* 0x1200 */ u32 m1200;
    /* 0x1204 */ u32 m1204;
    /* 0x1208 */ u16 m1208;
    /* 0x120C */ int m120C;
    /* 0x1210 */ u8 m1210;
    /* 0x1212 */ s16 m1212;
    /* 0x1214 */ s8 m1214;
    /* 0x1215 */ s8 m1215;
    /* 0x1216 */ s8 m1216;
    /* 0x1217 */ s8 m1217;
    /* 0x1218 */ dPath* ppd;
    /* 0x121C */ s8 m121C;
    /* 0x121D */ u8 m121D;
    /* 0x121E */ s8 m121E;
    /* 0x121F */ s8 m121F;
    /* 0x1220 */ daObj_Search::Act_c* mpSearchLight;
    /* 0x1224 */ s16 m1224;
    /* 0x1226 */ u8 m1226[0x1228 - 0x1226];
    /* 0x1228 */ s16 m1228;
    /* 0x122A */ s16 m122A;
    /* 0x122C */ s8 m122C;
    /* 0x1230 */ J3DMaterialTable* m1230;
    /* 0x1234 */ s8 m1234;
    /* 0x1236 */ s16 m1236;
    /* 0x1238 */ cXyz m1238;
    /* 0x1244 */ cXyz m1244;
    /* 0x1250 */ u8 m1250[0x1260 - 0x1250];
    /* 0x1260 */ f32 m1260;
    /* 0x1264 */ enemyice mEnemyIce;
    /* 0x161C */ enemyfire mEnemyFire;
    /* 0x1844 */ JntHit_c* mpJntHit;
};  // Size: 0x1848

class bkHIO_c : public JORReflexible {
public:
    bkHIO_c() {
        /* Nonmatching */
        m005 = 0x0;
        m006 = 0x0;
        m007 = 0x0;
        m008 = 0x1;
        m009 = 0x0;
        m00A = 0x0;
        m01C = 1.0f;
        m020 = 25.0f;
        m00C = 0x4;
        m024 = 25.0f;
        m028 = 1000.0f;
        m02C = 400.0f;
        m030 = 240.0f;
        m034 = 0x6590;
        m038 = 300.0f;
        m03C = 500.0f;
        m040 = 300.0f;
        m044 = 500.0f;
        m048 = -125.0f;
        m04C = 12.0f;
        m050 = 60.0f;
        m054 = 45.0f;
        m058 = 70.0f;
        m05C = 90.0f;
        m068 = 90.0f;
        m06C = 2.0f;
        m070 = 1.0f;
        m074 = 1.5f;
        m060 = 20.0f;
        m064 = 20.0f;
        m078 = 0x23;
        m07C = 50.0f;
        m080 = 25.0f;
        m084 = 25.0f;
        m088 = 50.0f;
        m08C = 0x1e;
        m08E = 0x12c;
        m090 = 1.2f;
        m094 = 1.0f;
        m098 = 1.0f;
        m09C = 10.0f;
        m0A0 = 0x17;
        m0A2 = 0x1;
        m0A4 = 0x1;
        m0A6 = 0x0;
        m0A8[0] = 1.0f;
        m0A8[1] = 1.0f;
        m0A8[2] = 1.0f;
        m0A8[3] = 1.0f;
        m0A8[4] = 1.0f;
        m0A8[5] = 1.0f;
        m0A8[6] = 1.0f;
        m0A8[7] = 1.0f;
        m0A8[8] = 1.0f;
        m0A8[9] = 1.0f;
        m0D0 = 0x5;
        m0D2 = 0x1;
        m0D4 = 0x1;
        m0D6 = 0x1;
        m0D8[0] = 1.0f;
        m0D8[1] = 1.0f;
        m0D8[2] = 1.0f;
        m0D8[3] = 0.8f;
        m0D8[4] = 0.5f;
        m0D8[5] = 1.0f;
        m0D8[6] = 1.0f;
        m0D8[7] = 1.0f;
        m0D8[8] = 1.0f;
        m0D8[9] = 1.0f;
        m100 = -60.0f;
        m018 = 0.7f;
        m104 = 0xc8;
        m106 = 0x1f4;
        m108 = 0x12c;
        m10A = 0x258;
        m010 = 0.0f;
        m014 = 400.0f;
    }
    virtual ~bkHIO_c() {}

public:
    /* 0x004 */ s8 mChildID;
    /* 0x005 */ u8 m005;
    /* 0x006 */ u8 m006;
    /* 0x007 */ u8 m007;
    /* 0x008 */ u8 m008;
    /* 0x009 */ u8 m009;
    /* 0x00A */ u8 m00A;
    /* 0x00B */ u8 m00B[0x00C - 0x00B];
    /* 0x00C */ s16 m00C;
    /* 0x00E */ u8 m00E[0x010 - 0x00E];
    /* 0x010 */ f32 m010;
    /* 0x014 */ f32 m014;
    /* 0x018 */ f32 m018;
    /* 0x01C */ f32 m01C;
    /* 0x020 */ f32 m020;
    /* 0x024 */ f32 m024;
    /* 0x028 */ f32 m028;
    /* 0x02C */ f32 m02C;
    /* 0x030 */ f32 m030;
    /* 0x034 */ s16 m034;
    /* 0x036 */ u8 m036[0x038 - 0x036];
    /* 0x038 */ f32 m038;
    /* 0x03C */ f32 m03C;
    /* 0x040 */ f32 m040;
    /* 0x044 */ f32 m044;
    /* 0x048 */ f32 m048;
    /* 0x04C */ f32 m04C;
    /* 0x050 */ f32 m050;
    /* 0x054 */ f32 m054;
    /* 0x058 */ f32 m058;
    /* 0x05C */ f32 m05C;
    /* 0x060 */ f32 m060;
    /* 0x064 */ f32 m064;
    /* 0x068 */ f32 m068;
    /* 0x06C */ f32 m06C;
    /* 0x070 */ f32 m070;
    /* 0x074 */ f32 m074;
    /* 0x078 */ s16 m078;
    /* 0x07A */ u8 m07A[0x07C - 0x07A];
    /* 0x07C */ f32 m07C;
    /* 0x080 */ f32 m080;
    /* 0x084 */ f32 m084;
    /* 0x088 */ f32 m088;
    /* 0x08C */ s16 m08C;
    /* 0x08E */ s16 m08E;
    /* 0x090 */ f32 m090;
    /* 0x094 */ f32 m094;
    /* 0x098 */ f32 m098;
    /* 0x09C */ f32 m09C;
    /* 0x0A0 */ s16 m0A0;
    /* 0x0A2 */ s16 m0A2;
    /* 0x0A4 */ s16 m0A4;
    /* 0x0A6 */ s16 m0A6;
    /* 0x0A8 */ f32 m0A8[10];
    /* 0x0D0 */ s16 m0D0;
    /* 0x0D2 */ s16 m0D2;
    /* 0x0D4 */ s16 m0D4;
    /* 0x0D6 */ s16 m0D6;
    /* 0x0D8 */ f32 m0D8[10];
    /* 0x100 */ f32 m100;
    /* 0x104 */ s16 m104;
    /* 0x106 */ s16 m106;
    /* 0x108 */ s16 m108;
    /* 0x10A */ s16 m10A;
};

#endif /* D_A_BK_H */
