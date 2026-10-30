#include "GangManager/cGangInfoPrototype.h"
#include "rws/classfactory.h"

namespace GangManager
{
    const char *cGangInfoPrototype::RetClassName() const
    {
        return "cGangInfoPrototype";
    }
}

namespace GangManager
{
    static RWS::CClassFactory::CRegistrar cGangInfoPrototypeRegistrar(
        "cGangInfoPrototype", cGangInfoPrototype::MakeNew, 0xD0, false);
}
