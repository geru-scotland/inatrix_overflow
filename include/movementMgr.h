//
// Created by Geru on 2/5/22.
//

#ifndef INATRIX_OVERFLOW_MOVEMENTMGR_H
#include "defines.h"
#include <stdbool.h>

#define INATRIX_OVERFLOW_MOVEMENTMGR_H
#define MOVEMENT_INFO_SIZE 2

typedef enum{
    MOVEMENT_INATRIX_X = 0,
    MOVEMENT_INATRIX_Y
} MovementGfx;

typedef struct{
    int x;
    int y;
} Vector;

typedef struct{
    Vector* homePos;
    Vector* destinyPos;
    Sprite* sprite;
} Movement;

extern void movementMgr_allocateMovements(MovementGfx movGfx);
extern void movementMgr_initSystem();
extern void movementMgr_setHomePosition(MovementGfx moveGfx);
extern bool movementMgr_nextPositionReached(MovementGfx movGfx);
extern void movementMgr_destructor();

extern Movement* movementInfo[MOVEMENT_INFO_SIZE];
#endif //INATRIX_OVERFLOW_MOVEMENTMGR_H
