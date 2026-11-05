#include "rws/classfactory.h"
#include "GameManagement/cHUDPingProfile.h"
#include "cd2/memory.h"
#include <xtl.h>
#include "rw/rwmem.h"

namespace GameManagement
{
    float cHUDPingProfile::m_aPingTime[4];

    // CD2 inlines construction into MakeNew even with the XMemSet call.
    __forceinline cHUDPingProfile::cHUDPingProfile(const RWS::CAttributePacket &)
    {
        // CD2 calls the XDK vector memory-fill routine rather than the CRT intrinsic.
        XMemSet(m_aPingTime, 0, sizeof(m_aPingTime));
    }

    RWS::CAttributeHandler *cHUDPingProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHUDPingProfile(packet);
    }

    void cHUDPingProfile::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        RWS::CAttributeHandler::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cHUDPingProfile"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case CMD_PingTime_Weapon:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_aPingTime[0] = value; }
                break;
            case CMD_PingTime_Grenade:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_aPingTime[1] = value; }
                break;
            case CMD_PingTime_Targeted:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_aPingTime[2] = value; }
                break;
            case CMD_PingTime_Damaged:
                { float value = it->GetAs_float(); RwMemNative32(&value, 4); m_aPingTime[3] = value; }
                break;
            }
        }
    }

    const char *cHUDPingProfile::RetClassName() const
    {
        return "cHUDPingProfile";
    }

    static RWS::CClassFactory::CRegistrar cHUDPingProfileRegistrar(
        "cHUDPingProfile", cHUDPingProfile::MakeNew, 0x18, false);
}
