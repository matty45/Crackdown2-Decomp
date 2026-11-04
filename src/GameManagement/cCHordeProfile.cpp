#include "rws/classfactory.h"
#include "GameManagement/cCHordeProfile.h"

namespace GameManagement
{
    const char *cCHordeProfile::RetClassName() const
    {
        return "cCHordeProfile";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCHordeProfileRegistrar(
        "cCHordeProfile", cCHordeProfile::MakeNew, 0xd8, false);
}

#include "cd2/memory.h"

// CD2 0x82865320: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cCHordeProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cCHordeProfile;
    }
}
