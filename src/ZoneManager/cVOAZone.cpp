#include "rws/classfactory.h"
#include "ZoneManager/cVOAZone.h"
#include "cd2/memory.h"

namespace ZoneManager
{
    RWS::CAttributeHandler *cVOAZone::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVOAZone(packet);
    }

    const char *cVOAZone::RetClassName() const
    {
        return "cVOAZone";
    }

    cVOAZone::~cVOAZone()
    {
    }

    static RWS::CClassFactory::CRegistrar cVOAZoneRegistrar(
        "cVOAZone", cVOAZone::MakeNew, 0x100, false);
}
