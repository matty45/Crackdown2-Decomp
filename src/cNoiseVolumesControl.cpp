#include "rws/classfactory.h"
#include "unknown/cNoiseVolumesControl.h"

namespace unknown
{
    const char *cNoiseVolumesControl::RetClassName() const
    {
        return "cNoiseVolumesControl";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cNoiseVolumesControlRegistrar(
        "cNoiseVolumesControl", cNoiseVolumesControl::MakeNew, 0x1c, false);
}
