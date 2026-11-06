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
