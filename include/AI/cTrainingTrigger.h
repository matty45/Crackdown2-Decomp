// Base and fields from RuffKing (same offsets in CD2; size 0x110). CD2's destructor (0x82485720) destroys the GUID handler and
// calls the inline empty destructor of the base, then cPlayerTriggerBase's (0x8280DCC0).
#ifndef AI_cTrainingTrigger_H
#define AI_cTrainingTrigger_H

#include "ZoneManager/cPlayerTriggerZone.h"
#include "editor/guid_event_handler.h"
#include "cd2/layout.h"
#include "rws/attributes.h"

namespace AI
{
    class cTrainingTrigger : public ZoneManager::cPlayerTriggerZone
    {
    public:
        // CD2 0x82485720.
        virtual ~cTrainingTrigger();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x824855F0 (MakeNew calls it with the packet).
        cTrainingTrigger(const RWS::CAttributePacket &packet);

    protected:
        Editor::cGUIDEventHandler<cTrainingTrigger> m_EventHandler;
        unsigned char m_nTriggerFlags;
        float m_fMaxYScale;
        float m_fMaxXZScale;
        float m_fYOffset;

        CD2_LAYOUT_CHECKS(cTrainingTrigger,
            CD2_SIZE(cTrainingTrigger, 0x110)
            CD2_OFFSET(cTrainingTrigger, m_EventHandler, 0xE0)
            CD2_OFFSET(cTrainingTrigger, m_nTriggerFlags, 0xF4)
            CD2_OFFSET(cTrainingTrigger, m_fMaxYScale, 0xF8)
            CD2_OFFSET(cTrainingTrigger, m_fMaxXZScale, 0xFC)
            CD2_OFFSET(cTrainingTrigger, m_fYOffset, 0x100))
    };
}

#endif
