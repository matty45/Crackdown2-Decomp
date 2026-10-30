// AI::cAITargetingProfile: an AI targeting profile, set from RWS attributes. Layout from the RuffKing PDB, confirmed
// against CD2: size 0x3C (the registrar 0x82F841B8 and MakeNew 0x82451C60 allocate 0x3C bytes); the constructor
// 0x82451CC8 zeroes m_TargetData (0x18) and builds m_EventHandler (0x28); HandleAttributes (0x82451E18) stores the
// four scores at 0x18..0x24 by RuffKing's command IDs.
#ifndef AI_CAITARGETINGPROFILE_H
#define AI_CAITARGETINGPROFILE_H

#include "rws/attributes.h"
#include "editor/guid_event_handler.h"
#include "AI/tAITargetData.h"
#include "cd2/layout.h"

namespace AI
{
    class cAITargetingProfile : public RWS::CAttributeHandler
    {
    private:
        tAITargetData m_TargetData;
        Editor::cGUIDEventHandler<cAITargetingProfile> m_EventHandler;

    public:
        enum LoadParameterTypes
        {
            CMD_BasePoints = 0,
            CMD_Distance = 1,
            CMD_Damage = 2,
            CMD_Visibility = 3,
            SIZE_ATTRIBUTE = 4
        };

        static const char *const pcAITargetingProfileClassID;

        cAITargetingProfile(const RWS::CAttributePacket &attr);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleAttributes(const RWS::CAttributePacket &attr);
        const tAITargetData *RetData() const;

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &attr, bool bGlobal);
        static const char *RetRWSClassName();

        // No user-declared destructor: CD2's scalar deleting destructor (0x82451DB8) has no vptr stores.

        CD2_LAYOUT_CHECKS(cAITargetingProfile,
            CD2_SIZE(cAITargetingProfile, 0x3C)
            CD2_OFFSET(cAITargetingProfile, m_TargetData, 0x18)
            CD2_OFFSET(cAITargetingProfile, m_EventHandler, 0x28))
    };
}

#endif // AI_CAITARGETINGPROFILE_H
