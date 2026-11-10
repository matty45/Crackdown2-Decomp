// PHYSICS::cLaunchPad (Crackdown 2): STAND-IN. Name and base (RWS::CEventHandler, virtual destructor in slot 0)
// from RuffKing's Physics/LaunchPad/cLaunchPad.h. CD2's cLaunchPadLocation::MakeNew (0x82714020) allocates 0x1A0
// bytes and calls the out-of-line constructor 0x8232C168 with only the object; its destructor releases the pad
// through virtual slot 0 (the deleting destructor). Fields are not modelled.
#ifndef PHYSICS_CLAUNCHPAD_H
#define PHYSICS_CLAUNCHPAD_H

#include "rws/eventhandler.h"
#include "cd2/layout.h"

namespace PHYSICS
{
    class cLaunchPad : public RWS::CEventHandler
    {
    public:
        cLaunchPad();
        virtual ~cLaunchPad();
        // RuffKing overrides the event handler; CD2 body not identified.
        virtual void HandleEvents(RWS::CMsg &);

    private:
        unsigned char m_unmodelled4[0x1A0 - 0x4];

        CD2_LAYOUT_CHECKS(cLaunchPad,
            CD2_SIZE(cLaunchPad, 0x1A0))
    };
}

#endif // PHYSICS_CLAUNCHPAD_H
