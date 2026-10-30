// Matching update (2026-10-28): all seven mapped functions are strict EXACT,
// including MakeNew in plain and LTCG builds. The constructor notes below are historical.
// GangManager/cFactionConfigData.cpp: 6 of 7 functions byte-exact against Crackdown 2 (title update).
// Whole-file pilot 2 (2026-10-23, Sonnet 5.5; finished by Opus with the /Ob1 flag correction). Exact:
//   RetClassName 0x82676278, scalar deleting destructor 0x82676328, ~cFactionConfigData 0x82676378,
//   HandleAttributes 0x826763D8 (776 bytes), registrar initializer 0x82FDCB00 and at-exit destructor 0x83040248.
// Work in progress: MakeNew 0x826761B0. CD2 inlines the constructor into it; our code has the same stores, but its
// register allocation needs r31 where CD2 fits in r4-r11 (instruction-scheduling puzzle).
// Class names cConfigBase / cConfigB1 / cConfigB2 / cConfigList (see the header) are ours; the real names are unknown.
#include "GangManager/cFactionConfigData.h"
#include "AI/cFactionTargetingProfile.h"
#include "editor/guid_event_handler.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"

namespace Fun_Runtime
{
    // CD2's inlined sentinel initializes only its payload. The owning
    // cSafeDeletable constructor supplies both circular links afterward.
    inline cSafeDeletablePointerBase::cSafeDeletablePointerBase() : m_pPtr(0) {}
    inline cSafeDeletable::cSafeDeletable()
    {
        m_SafeDeletablePointerListHead.m_pNext = &m_SafeDeletablePointerListHead;
        m_SafeDeletablePointerListHead.m_pPrev = &m_SafeDeletablePointerListHead;
    }
}

namespace GangManager
{
    struct tFaction
    {
        unsigned char pad0[0x1C];
        unsigned int m_nField1C;
        unsigned char pad1[0x98 - 0x20];
        const AI::tAIFactionTargetData *m_pTargetingData;   // RuffKing: cFactionInfo::m_pTargetingData
        unsigned char pad2[0xA4 - 0x9C];
        unsigned int m_anLevelTriggers[6];
    };

    class cGangManager
    {
    public:
        unsigned char pad[0x30];
        tFaction *m_apFactions[6];
        static cGangManager *sm_pGangManager;
        static cGangManager *RetGangManager() { return sm_pGangManager; }
    };

    const char *const cFactionConfigData::pcFactionConfigDataClassID = "cFactionConfigData";

    cFactionConfigData::~cFactionConfigData()
    {
    }

    const char *cFactionConfigData::RetClassName() const
    {
        return pcFactionConfigDataClassID;
    }

    void cFactionConfigData::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        for (RWS::CAttributeCommandIterator it(packet, pcFactionConfigDataClassID); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 1:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_afLevelTriggers[0] = mem; }
                break;
            case 2:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_afLevelTriggers[1] = mem; }
                break;
            case 3:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_afLevelTriggers[2] = mem; }
                break;
            case 4:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_afLevelTriggers[3] = mem; }
                break;
            case 5:
                { float mem = it->GetAs_float(); RwMemNative32(&mem, 4); m_afLevelTriggers[4] = mem; }
                break;
            case 0:
                switch (rwSwap32(it->GetAs_UInt32()))
                {
                case 0: m_Faction = FACTION_CIVILIANS; break;
                case 1: m_Faction = FACTION_CELL; break;
                case 2: m_Faction = FACTION_AGENCY; break;
                case 3: m_Faction = FACTION_FREAKS; break;
                }
                break;
            case 6:
                m_pTargetingProfile = Editor::cGUIDLinker<AI::cFactionTargetingProfile>::LinkToObject(it->GetAs_RWSGUID());
                break;
            }
        }

        if (packet.IsInstanceCreationPacket())
        {
            tFaction *pFaction = cGangManager::RetGangManager()->m_apFactions[m_Faction];
            if (pFaction)
            {
                pFaction->m_anLevelTriggers[0] = 0;
                for (unsigned char i = 1; i < 6; ++i)
                    pFaction->m_anLevelTriggers[i] = (unsigned int)m_afLevelTriggers[i - 1];
                pFaction->m_nField1C = pFaction->m_anLevelTriggers[5];
                const AI::tAIFactionTargetData *pData = m_pTargetingProfile->RetFactionTargetData();
                if (pData)
                    pFaction->m_pTargetingData = pData;
            }
        }
    }

    RWS::CAttributeHandler *cFactionConfigData::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cFactionConfigData(packet);
    }

    static RWS::CClassFactory::CRegistrar cFactionConfigDataRegistrar(
        "cFactionConfigData", cFactionConfigData::MakeNew, 0x50, false);
}


