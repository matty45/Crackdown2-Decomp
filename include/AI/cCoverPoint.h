// AI::cCoverPoint (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x823FD2A0, from its registrars in CD2's
// initializer run); RuffKing names the class in cCoverPoint.obj. No layout or virtuals are modelled yet.
#ifndef AI_CCOVERPOINT_H
#define AI_CCOVERPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cCoverPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CCOVERPOINT_H
