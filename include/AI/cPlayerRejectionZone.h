#include "rws/attributes.h"
// AI::cPlayerRejectionZone (Crackdown 2): STAND-IN.
// Its class-factory registrar (0x82F8FD58) registers "cPlayerRejectionZone" with MakeNew (0x8248B898) and size 0x100.
// Base and fields from RuffKing (same offsets in CD2; size 0x100). CD2's destructor (0x8248B9D0) destroys the GUID handler and
// calls the inline empty destructor of the base, then cPlayerTriggerBase's (0x8280DCC0).
#ifndef AI_CPLAYERREJECTIONZONE_H
#define AI_CPLAYERREJECTIONZONE_H

#include "ZoneManager/cPlayerTriggerZone.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"

namespace AI
{
    class cPlayerRejectionZone : public ZoneManager::cPlayerTriggerZone
    {
    public:
        // The reference declares both callbacks; CD2 installs concrete entries at primary slots 16 and 17.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // CD2 0x8248B9D0.
        virtual ~cPlayerRejectionZone();
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

    protected:
        Editor::cGUIDEventHandler<cPlayerRejectionZone> m_EventHandler;
        float m_fTimer;
        float m_fCurrentTimer;
        float m_fImpulse;

        // CD2: cPlayerRejectionZone's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x822A9A00
        virtual bool DoCollision(CHARACTER::cCharacter *); // 11: 0x8248BA38
    protected:
        CD2_LAYOUT_CHECKS(cPlayerRejectionZone,
            CD2_SIZE(cPlayerRejectionZone, 0x100)
            CD2_OFFSET(cPlayerRejectionZone, m_EventHandler, 0xE0)
            CD2_OFFSET(cPlayerRejectionZone, m_fTimer, 0xF4)
            CD2_OFFSET(cPlayerRejectionZone, m_fCurrentTimer, 0xF8)
            CD2_OFFSET(cPlayerRejectionZone, m_fImpulse, 0xFC))
    };
}

#endif // AI_CPLAYERREJECTIONZONE_H
