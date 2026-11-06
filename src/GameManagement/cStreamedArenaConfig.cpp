// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "rws/classfactory.h"
#include "GameManagement/cStreamedArenaConfig.h"

namespace GameManagement
{
    const char *cStreamedArenaConfig::RetClassName() const
    {
        return "cStreamedArenaConfig";
    }

    static RWS::CClassFactory::CRegistrar cStreamedArenaConfigRegistrar(
        "cStreamedArenaConfig", cStreamedArenaConfig::MakeNew, 0x28, false);
}
