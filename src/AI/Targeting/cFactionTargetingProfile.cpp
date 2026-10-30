// AI/Targeting/cFactionTargetingProfile.cpp: byte-exact against Crackdown 2 (title update), all 7 functions.
//   0x82451FA0 MakeNew            0x82452008 constructor       0x82451FF8 RetClassName
//   0x82452100 scalar deleting destructor (compiler-generated, emitted here)
//   0x82452160 HandleAttributes
//   0x82F84518 / 0x8303AD98 dynamic initializer / at-exit destructor of cFactionTargetingProfileRegistrar
#include <string.h>
#include "AI/cFactionTargetingProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"

namespace AI
{
    const char *const cFactionTargetingProfile::pcFactionTargetingProfileClassID = "cFactionTargetingProfile";

    cFactionTargetingProfile::cFactionTargetingProfile(const RWS::CAttributePacket &attr)
    {
        memset(&m_FactionData, 0, sizeof(m_FactionData));
        m_EventHandler.Register(this, attr.GetInstanceId());
    }

    const char *cFactionTargetingProfile::RetClassName() const
    {
        return pcFactionTargetingProfileClassID;
    }

    void cFactionTargetingProfile::HandleAttributes(const RWS::CAttributePacket &attr)
    {
        for (RWS::CAttributeCommandIterator it(attr, pcFactionTargetingProfileClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case CMD_CIVILIANS:
                SetupTargetData(it->GetAs_RWSGUID(), GangManager::FACTION_CIVILIANS);
                break;
            case CMD_FREAKS:
                SetupTargetData(it->GetAs_RWSGUID(), GangManager::FACTION_FREAKS);
                break;
            case CMD_AGENCY:
                SetupTargetData(it->GetAs_RWSGUID(), GangManager::FACTION_AGENCY);
                break;
            case CMD_CELL:
                SetupTargetData(it->GetAs_RWSGUID(), GangManager::FACTION_CELL);
                break;
            case CMD_AGENT:
                SetupTargetData(it->GetAs_RWSGUID(), GangManager::FACTION_AGENT);
                break;
            case CMD_AGENT_ROGUE:
                SetupTargetData(it->GetAs_RWSGUID(), GangManager::FACTION_AGENT_ROGUE);
                break;
            case CMD_Switch:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_FactionData.m_fSwitchThreshold = mem; }
                break;
            case CMD_MaxDistance:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_FactionData.m_fDistanceLimitRecip = 1.0f / mem; }
                break;
            case CMD_MaxDamage:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_FactionData.m_fDamageLimitRecip = 1.0f / mem; }
                break;
            }
        }
    }

    RWS::CAttributeHandler *cFactionTargetingProfile::MakeNew(const RWS::CAttributePacket &attr, bool)
    {
        return new cFactionTargetingProfile(attr);
    }

    static RWS::CClassFactory::CRegistrar cFactionTargetingProfileRegistrar(
        "cFactionTargetingProfile", cFactionTargetingProfile::MakeNew, 0x50, false);
}
