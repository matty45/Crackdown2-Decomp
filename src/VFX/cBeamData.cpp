#include "rws/classfactory.h"
#include "VFX/cBeamData.h"

namespace VFX
{
    const char *cBeamData::RetClassName() const
    {
        return "cBeamData";
    }
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cBeamDataRegistrar(
        "cBeamData", cBeamData::MakeNew, 0x88, false);
}
