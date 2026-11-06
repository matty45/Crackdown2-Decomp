// AI constants: static objects defined in the header, one copy per object file. Names and header from the RuffKing PDB
// (shared/ai/aiconstants.h: fFACING_TARGET_MIN_DOT_PRODUCT's initializer at line 17, fPOINT_LOCK_RADIUS_SQ's at line
// 27); values from CD2. CD2 has a third initializer between the two, cos(90 degrees), in the same ~660 objects:
// RuffKing defines that value as AI::fTARGET_FACING_ME_MIN_DOT_PRODUCT (same double argument) in
// caitargetcharacterinfo.cpp, so CD2 still had it in this header. fPOINT_LOCK_RADIUS is in initialised data in RuffKing
// (computed, then folded by link-time code generation) and holds fCHARACTER_HALF_HEIGHT's value, 0.9.
#ifndef AI_AICONSTANTS_H
#define AI_AICONSTANTS_H

#include <math.h>

static const float fCHARACTER_HALF_HEIGHT = 0.9f;
static const float fFACING_TARGET_MAX_ANGLE = 10.0f * 0.017453f;
static const float fFACING_TARGET_MIN_DOT_PRODUCT = (float)cos((double)fFACING_TARGET_MAX_ANGLE);

namespace AI
{
    static const float fTARGET_FACING_ME_MIN_DOT_PRODUCT = (float)cos(90.0 * 0.017453f);
}

static const float fPOINT_LOCK_RADIUS = fCHARACTER_HALF_HEIGHT;
static const float fPOINT_LOCK_RADIUS_SQ = fPOINT_LOCK_RADIUS * fPOINT_LOCK_RADIUS;

#endif // AI_AICONSTANTS_H
