// AI/Mission/AU/cBeaconDropPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/AU/cBeaconDropPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "AI/cBeaconDropPoint.h"
#include "cd2/memory.h"

namespace AI
{
    static RWS::CClassFactory::CRegistrar cBeaconDropPointRegistrar(
        "cBeaconDropPoint", cBeaconDropPoint::MakeNew, 0x60, false);
}
