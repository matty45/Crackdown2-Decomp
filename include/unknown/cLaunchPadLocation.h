// cLaunchPadLocation (Crackdown 2): STAND-IN. RuffKing names it PHYSICS::cLaunchPadLocation, derived from
// GameManagement::cNetGameSpawnPoint, with m_pLaunchPad (0x80), m_EventHandler (0x84) and m_pTarget (0x98), 0xA0
// bytes. CD2's MakeNew (0x82714020) calls the shared spawn-point constructor 0x8284D908, stores the class table
// 0x82139ED0, clears 0x80, builds the GUID handler at 0x84 and allocates the launch pad; the destructor (0x82714170)
// releases the pad, destroys the handler and calls the spawn-point destructor 0x8284D9E0. The namespace stays
// `unknown` for the existing matched symbols.
#ifndef unknown_cLaunchPadLocation_H
#define unknown_cLaunchPadLocation_H

#include "rws/attributes.h"
#include "GameManagement/cNetGameSpawnPoint.h"
#include "editor/guid_event_handler.h"
#include "PHYSICS/cLaunchPad.h"

namespace LaunchPad { class cLaunchPadTargetLocation; }

namespace unknown
{
    class cLaunchPadLocation : public GameManagement::cNetGameSpawnPoint
    {
    public:
        virtual ~cLaunchPadLocation();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        PHYSICS::cLaunchPad *m_pLaunchPad;
        Editor::cGUIDEventHandler<cLaunchPadLocation> m_EventHandler;
        LaunchPad::cLaunchPadTargetLocation *m_pTarget;

        CD2_LAYOUT_CHECKS(cLaunchPadLocation,
            CD2_SIZE(cLaunchPadLocation, 0xA0)
            CD2_OFFSET(cLaunchPadLocation, m_pLaunchPad, 0x80)
            CD2_OFFSET(cLaunchPadLocation, m_EventHandler, 0x84)
            CD2_OFFSET(cLaunchPadLocation, m_pTarget, 0x98))
    };
}

#endif
