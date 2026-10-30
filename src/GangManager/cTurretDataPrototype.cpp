#include "GangManager/cTurretDataPrototype.h"
#include "rws/classfactory.h"

namespace GangManager
{
    const char *cTurretDataPrototype::RetClassName() const
    {
        return "cTurretDataPrototype";
    }
}

namespace GangManager
{
    static RWS::CClassFactory::CRegistrar cTurretDataPrototypeRegistrar(
        "cTurretDataPrototype", cTurretDataPrototype::MakeNew, 0x40, false);
}
