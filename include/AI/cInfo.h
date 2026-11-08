// AI::cInfo (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x823FE9D8, from its registrars in CD2's
// initializer run); RuffKing names the class in cInfo.obj. No layout or virtuals are modelled yet.
#ifndef AI_CINFO_H
#define AI_CINFO_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cInfo
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AI_CINFO_H
