#ifndef D_A_PEDESTAL_H
#define D_A_PEDESTAL_H

#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

namespace daPedestal {

    class daPds_infiniteEcallBack_c : public dPa_levelEcallBack {
    public:
        virtual ~daPds_infiniteEcallBack_c() {}

        void execute(JPABaseEmitter*);
        void end();
        void makeEmitter(u16, const cXyz*, const csXyz*, const cXyz*);

        JPABaseEmitter* getEmitter() { return mpEmitter; }
        void setAngle(const csXyz* angle) { mpAngle = angle; }
        void setPos(const cXyz* pos) { mpPos = pos; }
        void setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) { mpEmitter = emitter; }

    private:
        /* 0x04 */ JPABaseEmitter* mpEmitter;
        /* 0x08 */ const cXyz* mpPos;
        /* 0x08 */ const csXyz* mpAngle;
    };

    class daPds_c : public fopAc_ac_c {
    public:
        enum ActionStatus {
            ACTION_STARTING = 0,
            ACTION_ONGOING  = 1,
            ACTION_ENDING   = -1,
        };

        typedef int (daPds_c::* ActionFunc_t)(void*);

        bool _delete();
        BOOL CreateHeap();
        void CreateInit();
        cPhs_State _create();
        int getMyStaffId();
        BOOL wakeupCheck();
        BOOL finishCheck();
        BOOL setAction(ActionFunc_t, void*);
        void action(void*);
        BOOL waitAction(void*);
        BOOL eventProc();
        void initialDefault(int);
        BOOL actionDefault(int);
        void initialMoveEvent(int);
        BOOL actionMoveEvent(int);
        void initialEffectSet(int);
        void initialEffectEnd(int);
        void set_mtx();
        BOOL initBrkAnm(u8, bool);
        void playBrkAnm();
        bool _execute();
        bool _draw();

        static const char m_arcname[];

    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_brkAnm mBrk;
        /* 0x2B4 */ Mtx mMtx;
        /* 0x2E4 */ dBgW* mpBgW;
        /* 0x2E8 */ daPds_infiniteEcallBack_c mOctagonGlowCb;
        /* 0x2F8 */ ActionFunc_t mAction;
        /* 0x304 */ f32 mTargetYPos;
        /* 0x308 */ f32 unk308;
        /* 0x30C */ s8 mActionStatus;
        /* 0x30D */ u8 mType;
        /* 0x30E */ u8 unk30E;
        /* 0x30F */ s8 unk30F;
        /* 0x310 */ s16 unk310;
        /* 0x312 */ s16 unk312;
        /* 0x314 */ s16 unk314;
        /* 0x316 */ s16 unk316;
        /* 0x318 */ u8 pad318[4];
        /* 0x31C */ f32 unk31C;
        /* 0x320 */ u8 pad320[4];
    };
};  // namespace daPedestal

#endif /* D_A_PEDESTAL_H */
