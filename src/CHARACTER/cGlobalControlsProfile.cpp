#include "CHARACTER/cGlobalControlsProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace CHARACTER
{
    const char *cGlobalControlsProfile::RetClassName() const
    {
        return "cGlobalControlsProfile";
    }

    static RWS::CClassFactory::CRegistrar cGlobalControlsProfileRegistrar(
        "cGlobalControlsProfile", cGlobalControlsProfile::MakeNew, 0x18C, false);

    // CD2 0x82558778: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cGlobalControlsProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cGlobalControlsProfile;
    }
}
