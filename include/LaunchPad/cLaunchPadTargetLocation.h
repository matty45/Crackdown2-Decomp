#ifndef LaunchPad_cLaunchPadTargetLocation_H
#define LaunchPad_cLaunchPadTargetLocation_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "editor/guid_event_handler.h"
#include "fun_runtime/vec3.h"

namespace PHYSICS { class cLaunchPadLocation; }

namespace LaunchPad
{
    // STAND-IN: RuffKing field names and base order; CD2 constructor 0x82714450
    // places the handler at 0x1C and the position at 0x30 (0x40 bytes total).
    class cLaunchPadTargetLocation : public RWS::CAttributeHandler, public RWS::CSystemCommands
    {
    public:
        cLaunchPadTargetLocation(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        PHYSICS::cLaunchPadLocation *m_pLaunch;
        Editor::cGUIDEventHandler<cLaunchPadTargetLocation> m_EventHandler;
        Fun_Runtime::Vec3 m_vPosition;
        // No user-declared destructor: CD2's deleting wrapper omits the derived-vptr store.
        CD2_LAYOUT_CHECKS(cLaunchPadTargetLocation,
            CD2_SIZE(cLaunchPadTargetLocation, 0x40)
            CD2_OFFSET(cLaunchPadTargetLocation, m_pLaunch, 0x18)
            CD2_OFFSET(cLaunchPadTargetLocation, m_EventHandler, 0x1C)
            CD2_OFFSET(cLaunchPadTargetLocation, m_vPosition, 0x30))
    };
}

#endif
