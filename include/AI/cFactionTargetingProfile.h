// AI::cFactionTargetingProfile: per-faction targeting profiles, set from RWS attributes. Layout from the RuffKing PDB,
// confirmed against CD2: size 0x50 (the registrar 0x82F84518 and MakeNew 0x82451FA0 allocate 0x50 bytes); the
// constructor 0x82452008 zeroes m_FactionData (0x18) and builds m_EventHandler (0x3C).
// SetupTargetData is the function at 0x824523F0, right after HandleAttributes (which calls it for commands 0..5); it is
// outside this file's range in config/splits.txt and not matched yet.
#ifndef AI_CFACTIONTARGETINGPROFILE_H
#define AI_CFACTIONTARGETINGPROFILE_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "AI/tAIFactionTargetData.h"
#include "GangManager/eFactions.h"
#include "cd2/layout.h"

namespace AI
{
    class cFactionTargetingProfile : public RWS::CAttributeHandler
    {
    private:
        tAIFactionTargetData m_FactionData;
        Editor::cGUIDEventHandler<cFactionTargetingProfile> m_EventHandler;

    public:
        enum LoadParameterTypes
        {
            CMD_CIVILIANS = 0,
            CMD_FREAKS = 1,
            CMD_AGENCY = 2,
            CMD_CELL = 3,
            CMD_AGENT = 4,
            CMD_AGENT_ROGUE = 5,
            CMD_Switch = 6,
            CMD_MaxDistance = 7,
            CMD_MaxDamage = 8,
            SIZE_ATTRIBUTE = 9
        };

        static const char *const pcFactionTargetingProfileClassID;

        cFactionTargetingProfile(const RWS::CAttributePacket &attr);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        const tAIFactionTargetData *RetFactionTargetData() const { return &m_FactionData; } // inline in CD2

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &attr, bool bGlobal);
        static const char *RetRWSClassName();

    private:
        void SetupTargetData(const RWS::RWSGUID nFaction, GangManager::eFactions eFaction);

        // No user-declared destructor: CD2's scalar deleting destructor (0x82452100) has no vptr stores.

    public:
        CD2_LAYOUT_CHECKS(cFactionTargetingProfile,
            CD2_SIZE(cFactionTargetingProfile, 0x50)
            CD2_OFFSET(cFactionTargetingProfile, m_FactionData, 0x18)
            CD2_OFFSET(cFactionTargetingProfile, m_EventHandler, 0x3C))
    };
}

#endif // AI_CFACTIONTARGETINGPROFILE_H
