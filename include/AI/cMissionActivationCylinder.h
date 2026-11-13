// Base and fields from RuffKing (same offsets in CD2; size 0x110). CD2's destructor (0x8248B058) destroys the GUID handler and
// calls the inline empty destructor of the base, then cPlayerTriggerBase's (0x8280DCC0).
#ifndef AI_cMissionActivationCylinder_H
#define AI_cMissionActivationCylinder_H

#include "ZoneManager/cPlayerTriggerCylinder.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"

#include "rws/attributes.h"

namespace AI
{
    class cMissionActivationCylinder : public ZoneManager::cPlayerTriggerCylinder
    {
    public:
        // The reference declares both callbacks; CD2 installs concrete entries at primary slots 16 and 17.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // __forceinline: CD2's MakeNew (0x8248AF38) expands it after the base constructor call and passes no packet.
        __forceinline cMissionActivationCylinder() : m_bMissionCritical(false) {}
        // CD2 0x8248B058.
        virtual ~cMissionActivationCylinder();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    protected:
        Editor::cGUIDEventHandler<cMissionActivationCylinder> m_EventHandler;
        bool m_bMissionCritical;

        // CD2: cMissionActivationCylinder's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8248B0C0
    protected:
        CD2_LAYOUT_CHECKS(cMissionActivationCylinder,
            CD2_SIZE(cMissionActivationCylinder, 0x110)
            CD2_OFFSET(cMissionActivationCylinder, m_EventHandler, 0xF0)
            CD2_OFFSET(cMissionActivationCylinder, m_bMissionCritical, 0x104))
    };
}

#endif
