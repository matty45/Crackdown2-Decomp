// AI::cHeliDropPoint (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82475698, from its registrars in CD2's
// initializer run); RuffKing names the class in cTacticalObjective.obj. No layout or virtuals are modelled yet.
#ifndef AI_CHELIDROPPOINT_H
#define AI_CHELIDROPPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cHeliDropPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CHELIDROPPOINT_H
