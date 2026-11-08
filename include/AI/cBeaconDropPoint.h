// AI::cBeaconDropPoint (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x824609F8, from its registrars in CD2's
// initializer run); RuffKing names the class in cBeaconDropPoint.obj. No layout or virtuals are modelled yet.
#ifndef AI_CBEACONDROPPOINT_H
#define AI_CBEACONDROPPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cBeaconDropPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CBEACONDROPPOINT_H
