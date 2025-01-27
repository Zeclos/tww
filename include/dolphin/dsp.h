#ifndef _DOLPHIN_DSP
#define _DOLPHIN_DSP

#include "dolphin/os/OS.h"
#include "dolphin/types.h"
#include "dolphin/os/OSUtil.h"

volatile u16 __DSPRegs[32] AT_ADDRESS(0xCC005000);
volatile u32 __AIRegs[8] AT_ADDRESS(0xCC006C00);

#ifdef __cplusplus
extern "C" {
#endif

#define DSP_TASK_FLAG_CLEARALL 0x00000000
#define DSP_TASK_FLAG_ATTACHED 0x00000001
#define DSP_TASK_FLAG_CANCEL 0x00000002

#define DSP_TASK_STATE_INIT 0
#define DSP_TASK_STATE_RUN 1
#define DSP_TASK_STATE_YIELD 2
#define DSP_TASK_STATE_DONE 3

#define DSP_MAILBOX_IN_HI (0)
#define DSP_MAILBOX_IN_LO (1)
#define DSP_MAILBOX_OUT_HI (2)
#define DSP_MAILBOX_OUT_LO (3)
#define DSP_CONTROL_STATUS (5)

#define DSP_ARAM_SIZE (9)
#define DSP_ARAM_MODE (11)
#define DSP_ARAM_REFRESH (13)
#define DSP_ARAM_DMA_MM_HI (16)  // Main mem address
#define DSP_ARAM_DMA_MM_LO (17)
#define DSP_ARAM_DMA_ARAM_HI (18)  // ARAM address
#define DSP_ARAM_DMA_ARAM_LO (19)
#define DSP_ARAM_DMA_SIZE_HI (20)  // DMA buffer size
#define DSP_ARAM_DMA_SIZE_LO (21)

#define DSP_DMA_START_HI (24)  // DMA start address
#define DSP_DMA_START_LO (25)
#define DSP_DMA_CONTROL_LEN (27)
#define DSP_DMA_BYTES_LEFT (29)

#define DSP_DMA_START_FLAG (0x8000)  // set to start DSP

typedef void (*DSPCallback)(void* task);

typedef struct STRUCT_DSP_TASK {
    /* 0x00 */ vu32 state;
    /* 0x04 */ vu32 priority;
    /* 0x08 */ vu32 flags;
    /* 0x0C */ u16* iram_mmem_addr;
    /* 0x10 */ u32 iram_length;
    /* 0x14 */ u32 iram_addr;

    /* 0x18 */ u16* dram_mmem_addr;
    /* 0x1C */ u32 dram_length;
    /* 0x20 */ u32 dram_addr;

    /* 0x24 */ u16 dsp_init_vector;
    /* 0x26 */ u16 dsp_resume_vector;

    /* 0x28 */ DSPCallback init_cb;
    /* 0x2C */ DSPCallback res_cb;
    /* 0x30 */ DSPCallback done_cb;
    /* 0x34 */ DSPCallback req_cb;

    /* 0x38 */ struct STRUCT_DSP_TASK* next;
    /* 0x3C */ struct STRUCT_DSP_TASK* prev;

    /* 0x40 */ OSTime t_context;
    /* 0x48 */ OSTime t_task;
} DSPTaskInfo;  // Size: 0x50

extern DSPTaskInfo* __DSP_tmp_task;
extern DSPTaskInfo* __DSP_last_task;
extern DSPTaskInfo* __DSP_first_task;
extern DSPTaskInfo* __DSP_curr_task;

u32 DSPCheckMailToDSP();
u32 DSPCheckMailFromDSP();
u32 DSPReadMailFromDSP();
void DSPSendMailToDSP(u32 mail);
void DSPAssertInt();
void DSPInit();
void DSPReset();
void DSPHalt();
u32 DSPGetDMAStatus();
DSPTaskInfo* DSPAddTask(DSPTaskInfo* task);

void __DSP_exec_task(DSPTaskInfo* curr, DSPTaskInfo* next);
void __DSP_boot_task(DSPTaskInfo* task);
void __DSP_insert_task(DSPTaskInfo* task);
void __DSP_add_task(DSPTaskInfo* task);
void __DSP_remove_task(DSPTaskInfo* task);
void __DSP_debug_printf(const char* fmt, ...);

#ifdef __cplusplus
}
#endif

#endif  // _DOLPHIN_DSP
