#include "rws/classfactory.h"
#include "GameManagement/cCHordeCaptureZone.h"

namespace GameManagement
{
    const char *cCHordeCaptureZone::RetClassName() const
    {
        return "cCHordeCaptureZone";
    }
}

namespace GameManagement
{
    static RWS::CClassFactory::CRegistrar cCHordeCaptureZoneRegistrar(
        "cCHordeCaptureZone", cCHordeCaptureZone::MakeNew, 0x390, false);
}

#include "cd2/memory.h"

// CD2 0x82858CD0: the class-factory constructor; the constructor stays out of line.
namespace GameManagement
{
    RWS::CAttributeHandler *cCHordeCaptureZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCHordeCaptureZone(packet);
    }
}
