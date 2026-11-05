#include "rws/classfactory.h"
#include "GameManagement/cCHordeCaptureZone.h"
#include "cd2/memory.h"

namespace GameManagement
{
    const char *cCHordeCaptureZone::RetClassName() const
    {
        return "cCHordeCaptureZone";
    }

    static RWS::CClassFactory::CRegistrar cCHordeCaptureZoneRegistrar(
        "cCHordeCaptureZone", cCHordeCaptureZone::MakeNew, 0x390, false);

    // CD2 0x82858CD0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cCHordeCaptureZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCHordeCaptureZone(packet);
    }
}
