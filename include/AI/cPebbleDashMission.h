// AI::cPebbleDashMission (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82489D10, from its registrars in CD2's
// initializer run); RuffKing names the class in cPebbleDashMission.obj. No layout or virtuals are modelled yet.
#ifndef AI_CPEBBLEDASHMISSION_H
#define AI_CPEBBLEDASHMISSION_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cPebbleDashMission
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CPEBBLEDASHMISSION_H
