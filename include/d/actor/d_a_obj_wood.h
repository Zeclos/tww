#ifndef D_A_OBJ_WOOD_H
#define D_A_OBJ_WOOD_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

namespace daObjWood {
    class Act_c : public fopAc_ac_c {
    public:
        inline s32 _create();
        inline bool _delete();
        inline bool _execute();
        inline bool _draw();
    public:
        /* 0x290 */ u32 field_0x290[3];
        /* 0x2B4 */ dCcD_Stts mStts;
        /* 0x2D8 */ dCcD_Cyl mCyl;
    };

    namespace Method {
        s32 Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
    };
};

#endif /* D_A_OBJ_WOOD_H */
