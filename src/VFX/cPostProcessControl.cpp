#include "rws/classfactory.h"
#include "VFX/cPostProcessControl.h"

namespace VFX
{
    const char *cPostProcessControl::RetClassName() const
    {
        return "cPostProcessControl";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cPostProcessControlRegistrar(
        "cPostProcessControl", cPostProcessControl::MakeNew, 0x1c, false);
}
