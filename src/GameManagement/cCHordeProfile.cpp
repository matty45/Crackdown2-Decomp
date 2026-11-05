#include "rws/classfactory.h"
#include "GameManagement/cCHordeProfile.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCHordeProfile::RetClassName() const
    {
        return "cCHordeProfile";
    }

    static RWS::CClassFactory::CRegistrar cCHordeProfileRegistrar(
        "cCHordeProfile", cCHordeProfile::MakeNew, 0xd8, false);

    // CD2 0x82865320: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCHordeProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCHordeProfile;
    }
}
