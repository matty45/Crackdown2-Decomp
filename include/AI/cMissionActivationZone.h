// Base and fields from RuffKing (same offsets in CD2; size 0x100). CD2's destructor (0x8248B510) destroys the GUID handler and
// calls the inline empty destructor of the base, then cPlayerTriggerBase's (0x8280DCC0).
#ifndef AI_cMissionActivationZone_H
#define AI_cMissionActivationZone_H

#include "ZoneManager/cPlayerTriggerZone.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"

#include "rws/attributes.h"

namespace AI
{
    class cMissionActivationZone : public ZoneManager::cPlayerTriggerZone
    {
    public:
        // The reference declares both callbacks; CD2 installs concrete entries at primary slots 16 and 17.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // CD2 0x8248B510.
        virtual ~cMissionActivationZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    protected:
        Editor::cGUIDEventHandler<cMissionActivationZone> m_EventHandler;

        CD2_LAYOUT_CHECKS(cMissionActivationZone,
            CD2_SIZE(cMissionActivationZone, 0x100)
            CD2_OFFSET(cMissionActivationZone, m_EventHandler, 0xE0))
    };
}

#endif
