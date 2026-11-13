// AI::cPebbleDashMission (Crackdown 2): RuffKing's cPebbleDashMission.h gives the base (cMission), the fields and the
// size (0x3D0), which CD2's registrar confirms. CD2's MakeNew (0x82489D10) expands the constructor: cMission's
// constructor (0x824592E8), this class's tables at 0 (0x821056F8), 0x10, 0x240, 0x248 and 0x260, then the two zone
// pointers cleared; it returns the attribute handler at +0x248.
#ifndef AI_CPEBBLEDASHMISSION_H
#define AI_CPEBBLEDASHMISSION_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cMission.h"

namespace AI
{
    class cLocalPlayerTrigger;

    class cPebbleDashMission : public cMission
    {
    public:
        // RuffKing's state type; its values are not recovered.
        enum ePebbleDashMissionState { };

        // __forceinline: CD2 expands the constructor into MakeNew (docs/matching-notes.md, "Inlining").
        __forceinline cPebbleDashMission() : m_pTakeoffZone(0), m_pLandingZone(0) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPebbleDashMissionClass;   // CD2 0x8381D99C

        virtual const Fun_Runtime::cClass &RetClass() const;            // CD2 0x82489CA0
        virtual bool IsA(const Fun_Runtime::cClass &) const;            // CD2 0x82489CB0
        virtual const char *RetClassName() const;                       // CD2 0x82489DB0
        // CD2 0x8248A0C8; cBeaconMission's, cFinalMission's and cRefineryMission's identical bodies were folded into it.
        virtual void Activate();
        virtual void TickUpdate(float dT);                              // CD2 0x8248A0D0
        virtual void HandleAttributes(const RWS::CAttributePacket &);   // CD2 0x82489FA8 (attribute-handler slot 1)

    protected:
        cLocalPlayerTrigger *m_pTakeoffZone;                            // 0x3C0
        cLocalPlayerTrigger *m_pLandingZone;                            // 0x3C4
        ePebbleDashMissionState m_ePDState;                             // 0x3C8

        CD2_LAYOUT_CHECKS(cPebbleDashMission,
            CD2_SIZE(cPebbleDashMission, 0x3D0)
            CD2_OFFSET(cPebbleDashMission, m_pTakeoffZone, 0x3C0)
            CD2_OFFSET(cPebbleDashMission, m_ePDState, 0x3C8))
    };
}

#endif // AI_CPEBBLEDASHMISSION_H
