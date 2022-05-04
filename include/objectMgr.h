//
// Created by Geru on 2/5/22.
//

#ifndef INATRIX_OVERFLOW_OBJECTMGR_H
#define INATRIX_OVERFLOW_OBJECTMGR_H

#include <stdbool.h>
#include "matrix.h"

#define ANIMATIONS_SIZE 1
#define INATRIX_X_POS_Y 170

typedef enum{
    ANIMATION_BIT_SHAKE = 0
} AnimID;

typedef struct {
    bool active;
    int8 state;
} Animation;

extern uint8 INATRIX_XHOME_POS_X;
extern uint8 INATRIX_XHOME_POS_Y;
extern uint8 INATRIX_YHOME_POS_X;
extern uint8 INATRIX_YHOME_POS_Y;

extern void objectMgr_init();
extern void objectMgr_initAnimations();
extern void objectMgr_spawnInatrix();
extern void objectMgr_spawnCapsules();
extern void objectMgr_setAnimationActive(AnimID animID, bool active);

extern int objectMgr_objectAreaClicked(int x, int y);
extern void objectMgr_manageSelectedCapsule(int mode);

extern Animation* animations[ANIMATIONS_SIZE];
#endif //INATRIX_OVERFLOW_OBJECTMGR_H
