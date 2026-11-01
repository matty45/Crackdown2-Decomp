#include "rws/classfactory.h"
#include "unknown/cGodRaysControl.h"

namespace unknown
{
    const char *cGodRaysControl::RetClassName() const
    {
        return "cGodRaysControl";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cGodRaysControlRegistrar(
        "cGodRaysControl", cGodRaysControl::MakeNew, 0x1c, false);
}
