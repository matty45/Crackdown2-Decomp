// Physics constants: static objects defined in the header, so every object file that includes it has its own copy and
// its own dynamic initializers. Names, header and order from the RuffKing PDB (shared/physics/physicsconsts.h, lines
// 55, 56, 73 and 74); values from CD2, where about a thousand objects carry this initializer sequence. Each value is
// built from g_GlobalConstants.CONST_FLOAT_1, which CD2 (like RuffKing) loads from the object's own copy.
// RuffKing's CHAR_MAX_DELTA_MOVE (line 143) has no initializer in CD2's sequence, so it is not declared here.
#ifndef PHYSICS_PHYSICSCONSTS_H
#define PHYSICS_PHYSICSCONSTS_H

#include "fun_runtime/class.h"

static const float fPhysicsSimulationTick = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1 / 60.0f;
static const float fMAX_TIME_STEP = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1 * 0.05f;

static const float fSLIP_LIMIT = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1;
static const float fSKID_LIMIT = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_1;

#endif // PHYSICS_PHYSICSCONSTS_H
