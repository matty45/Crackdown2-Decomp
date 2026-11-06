// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "GangManager/cPedestrainDataPrototype.h"
#include "rws/classfactory.h"

namespace GangManager
{
    const char *cPedestrainDataPrototype::RetClassName() const
    {
        return "cPedestrainDataPrototype";
    }

    static RWS::CClassFactory::CRegistrar cPedestrainDataPrototypeRegistrar(
        "cPedestrainDataPrototype", cPedestrainDataPrototype::MakeNew, 0x44, false);
}
