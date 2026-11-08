// PHYSICS/cPickupProfile.cpp: RuffKing's Libraries/Shared/Physics/cPickupProfile.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "PHYSICS/cPickupProfile.h"
#include "cd2/memory.h"

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cPickupProfileRegistrar(
        "cPickupProfile", cPickupProfile::MakeNew, 0x18, false);
}
