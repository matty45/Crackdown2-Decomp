#include "AI/cForceFieldProfile.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cForceFieldProfile::RetClassName() const
    {
        return "cForceFieldProfile";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cForceFieldProfileRegistrar(
        "cForceFieldProfile", cForceFieldProfile::MakeNew, 0x130, false);
}

#include "cd2/memory.h"

// CD2 0x824889A0: the class-factory constructor; the constructor stays out of line.
namespace AI
{
    RWS::CAttributeHandler *cForceFieldProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cForceFieldProfile(packet);
    }
}
