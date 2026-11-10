// AI::cLocalPlayerTrigger (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82489C38, from its registrars in CD2's
// initializer run); RuffKing names the class in cPebbleDashMission.obj. No layout or virtuals are modelled yet.
#ifndef AI_CLOCALPLAYERTRIGGER_H
#define AI_CLOCALPLAYERTRIGGER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "ZoneManager/cPlayerTriggerZone.h"
#include "editor/guid_event_handler.h"

namespace AI
{
    // CD2 0x82489DC0 calls cPlayerTriggerBase(false), then installs the zone's
    // primary and load/save tables. RuffKing's later ActionIO base is absent.
    class cLocalPlayerTrigger : public ZoneManager::cPlayerTriggerZone
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        cLocalPlayerTrigger(const RWS::CAttributePacket &);
        virtual ~cLocalPlayerTrigger();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // CD2 table 0x821056A8: slots 18 and 19 follow the trigger interface.
        virtual const char *RetClassName() const;
        virtual void Destruct();

    private:
        // RuffKing names these members. CD2's constructor places the handler
        // immediately after the 0xE0-byte zone, then clears the flag byte at +0xF4.
        Editor::cGUIDEventHandler<cLocalPlayerTrigger> m_EventHandler;
        unsigned char m_nTriggerFlags;

        CD2_LAYOUT_CHECKS(cLocalPlayerTrigger,
            CD2_SIZE(cLocalPlayerTrigger, 0x100)
            CD2_OFFSET(cLocalPlayerTrigger, m_EventHandler, 0xE0)
            CD2_OFFSET(cLocalPlayerTrigger, m_nTriggerFlags, 0xF4))
    };
}

#endif // AI_CLOCALPLAYERTRIGGER_H
