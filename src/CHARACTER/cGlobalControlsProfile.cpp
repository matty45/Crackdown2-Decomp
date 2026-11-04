#include "CHARACTER/cGlobalControlsProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cGlobalControlsProfile::RetClassName() const
    {
        return "cGlobalControlsProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cGlobalControlsProfileRegistrar(
        "cGlobalControlsProfile", cGlobalControlsProfile::MakeNew, 0x18C, false);
}

#include "cd2/memory.h"

// CD2 0x82558778: the class-factory constructor; the constructor stays out of line.
namespace CHARACTER
{
    RWS::CAttributeHandler *cGlobalControlsProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGlobalControlsProfile;
    }
}
