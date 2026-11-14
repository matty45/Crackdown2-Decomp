// STAND-IN: RuffKing declares this class in cMission.h. CD2 factory 0x82458CC0
// confirms the ten objectives, GUID handler at +0x40 and complete size 0x54.
#ifndef AI_CSECONDARYOBJECTIVESINFO_H
#define AI_CSECONDARYOBJECTIVESINFO_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "fun_runtime/class.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    class cSecondaryObjectivesInfo : public RWS::CSystemCommands, public RWS::CAttributeHandler
    {
    public:
        enum eObjectiveType
        {
            eObjectiveType_None = 0, eObjectiveType_RoadRace, eObjectiveType_RooftopRace,
            eObjectiveType_TacLoc, eObjectiveType_Breach, eObjectiveType_AgilityRenegadeOrb,
            eObjectiveType_DrivingRenegadeOrb, eObjectiveType_VehicleStuntRing,
            eObjectiveType_WingsuitRing, eObjectiveType_Num
        };
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 expands construction and destruction into their allocation wrappers.
        __forceinline cSecondaryObjectivesInfo()
        {
            for (unsigned int i = 0; i < 10; ++i)
                m_Objectives[i] = eObjectiveType_None;
        }
        virtual ~cSecondaryObjectivesInfo() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        // CD2 table 0x82102CE8 has these reference-named slots 11..15.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleSystemCommands(const RWS::CAttributePacket &);
    private:
        eObjectiveType m_Objectives[10];
        Editor::cGUIDEventHandler<cSecondaryObjectivesInfo> m_EventHandler;
        CD2_LAYOUT_CHECKS(cSecondaryObjectivesInfo,
            CD2_SIZE(cSecondaryObjectivesInfo, 0x54)
            CD2_OFFSET(cSecondaryObjectivesInfo, m_Objectives, 0x18)
            CD2_OFFSET(cSecondaryObjectivesInfo, m_EventHandler, 0x40))
    };
}
#endif
