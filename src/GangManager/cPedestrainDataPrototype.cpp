#include "GangManager/cPedestrainDataPrototype.h"
#include "rws/classfactory.h"

namespace GangManager
{
    const char *cPedestrainDataPrototype::RetClassName() const
    {
        return "cPedestrainDataPrototype";
    }
}

namespace GangManager
{
    static RWS::CClassFactory::CRegistrar cPedestrainDataPrototypeRegistrar(
        "cPedestrainDataPrototype", cPedestrainDataPrototype::MakeNew, 0x44, false);
}
