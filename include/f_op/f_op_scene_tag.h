#ifndef F_F_OP_SCENE_TAG_H_
#define F_F_OP_SCENE_TAG_H_

#include "SSystem/SComponent/c_phase.h"
#include "f_pc/f_pc_create_tag.h"
#include "f_pc/f_pc_node.h"

struct scene_tag_class {
    /* 0x00 */ create_tag_class base;
};

void fopScnTg_QueueTo(scene_tag_class* pSceneTag);
void fopScnTg_ToQueue(scene_tag_class* pSceneTag);
void fopScnTg_Init(scene_tag_class* pSceneTag, void* pData);

extern node_list_class g_fopScnTg_SceneList;

#endif
