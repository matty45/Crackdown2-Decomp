#include "LaunchPad/cLaunchPadTargetLocation.h"
#include "cd2/memory.h"
#include "rws/classfactory.h"

namespace LaunchPad
{
    cLaunchPadTargetLocation::cLaunchPadTargetLocation(const RWS::CAttributePacket &packet)
    {
        m_EventHandler.Register(this, packet.GetInstanceId());
    }

    RWS::CAttributeHandler *cLaunchPadTargetLocation::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cLaunchPadTargetLocation(packet);
    }

    const char *cLaunchPadTargetLocation::RetClassName() const
    {
        return "cLaunchPadTargetLocation";
    }

    static RWS::CClassFactory::CRegistrar cLaunchPadTargetLocationRegistrar(
        "cLaunchPadTargetLocation", cLaunchPadTargetLocation::MakeNew, 0x40, false);
}
