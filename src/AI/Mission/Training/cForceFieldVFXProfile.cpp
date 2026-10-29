#include "AI/cForceFieldVFXProfile.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cForceFieldVFXProfile::RetClassName() const
    {
        return "cForceFieldVFXProfile";
    }

    RWS::CAttributeHandler *cForceFieldVFXProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        cForceFieldVFXProfile *p = new cForceFieldVFXProfile();
        return p;
    }

    static RWS::CClassFactory::CRegistrar cForceFieldVFXProfileRegistrar(
        "cForceFieldVFXProfile", cForceFieldVFXProfile::MakeNew, 0x18, false);
}
