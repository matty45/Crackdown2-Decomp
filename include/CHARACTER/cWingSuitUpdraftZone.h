// CHARACTER::cWingSuitUpdraftZone (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x827284D8, from its registrars in CD2's
// initializer run); RuffKing names the class in cWingSuitUpdraftZone.obj. No layout or virtuals are modelled yet.
#ifndef CHARACTER_CWINGSUITUPDRAFTZONE_H
#define CHARACTER_CWINGSUITUPDRAFTZONE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "ZoneManager/cPlayerTriggerCylinder.h"
#include "editor/guid_event_handler.h"

namespace CHARACTER
{
    class cWingSuitUpdraftZoneProfile;
    // Burn's cylinder base and members agree with CD2 factory 0x827284D8.
    class cWingSuitUpdraftZone : public ZoneManager::cPlayerTriggerCylinder
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 inlines this constructor after calling the cylinder constructor.
        __forceinline cWingSuitUpdraftZone(const RWS::CAttributePacket &) : m_pProfile(0) {}
        virtual ~cWingSuitUpdraftZone();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool DoCollision(cCharacter *);
        virtual void OnPlayerEnter(cCharacter *);
        virtual void OnPlayerLeave(cCharacter *);
        // CD2 table 0x8213D6E0 appends these at slots 18 and 19.
        virtual const char *RetClassName() const;
        virtual void Destruct();

    public:
        Editor::cGUIDEventHandler<cWingSuitUpdraftZone> m_EventHandler;

    private:
        cWingSuitUpdraftZoneProfile *m_pProfile;

        CD2_LAYOUT_CHECKS(cWingSuitUpdraftZone,
            CD2_SIZE(cWingSuitUpdraftZone, 0x110)
            CD2_OFFSET(cWingSuitUpdraftZone, m_EventHandler, 0xF0)
            CD2_OFFSET(cWingSuitUpdraftZone, m_pProfile, 0x104))
    };
}

#endif // CHARACTER_CWINGSUITUPDRAFTZONE_H
