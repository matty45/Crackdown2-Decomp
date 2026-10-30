#include "unknown/cCharacterDLCVFXProfile.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cCharacterDLCVFXProfile::RetClassName() const
    {
        return "cCharacterDLCVFXProfile";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cCharacterDLCVFXProfileRegistrar(
        "cCharacterDLCVFXProfile", cCharacterDLCVFXProfile::MakeNew, 0x1C, false);
}
