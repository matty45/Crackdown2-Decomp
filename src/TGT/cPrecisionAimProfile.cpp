#include "rws/classfactory.h"
#include "TGT/cPrecisionAimProfile.h"

namespace TGT
{
    const char *cPrecisionAimProfile::RetClassName() const
    {
        return "cPrecisionAimProfile";
    }
}

namespace TGT
{
    static RWS::CClassFactory::CRegistrar cPrecisionAimProfileRegistrar(
        "cPrecisionAimProfile", cPrecisionAimProfile::MakeNew, 0x18, false);
}
