// Character constants: static objects defined in the header, one copy per object file. Names, header and order from the
// RuffKing PDB (shared/character/characterconsts.h: the squared thresholds' initializers are lines 314 and 317); values
// from CD2. fWALK_VELOCITY_THRESHOLD is a constant (RuffKing keeps it in read-only data); HALF and DOUBLED are computed
// from it, which CD2's link-time code generation turned into initialised data (0.13 and 0.52), while the squares keep
// their initializers.
#ifndef CHARACTER_CHARACTERCONSTS_H
#define CHARACTER_CHARACTERCONSTS_H

#include "fun_runtime/randgen.h"

namespace CHARACTER
{
    static Fun_Runtime::cRandGen gRandGen;
}

static const float fWALK_VELOCITY_THRESHOLD = 0.26f;
static const float fWALK_VELOCITY_THRESHOLD_HALF = fWALK_VELOCITY_THRESHOLD * 0.5f;
static const float fWALK_VELOCITY_THRESHOLD_HALF_SQ = fWALK_VELOCITY_THRESHOLD_HALF * fWALK_VELOCITY_THRESHOLD_HALF;
static const float fWALK_VELOCITY_THRESHOLD_DOUBLED = fWALK_VELOCITY_THRESHOLD * 2.0f;
static const float fWALK_VELOCITY_THRESHOLD_DOUBLED_SQ =
    fWALK_VELOCITY_THRESHOLD_DOUBLED * fWALK_VELOCITY_THRESHOLD_DOUBLED;

#endif // CHARACTER_CHARACTERCONSTS_H
