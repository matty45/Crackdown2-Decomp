// AI::cChaseAndAttackPilotBehaviour (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824D29E0, MakeNew 0x824D2850, SpawnFromPrototype 0x824D28D0, from its registrars in CD2's
// initializer run); RuffKing names the class in ChaseAndAttackPilotBehaviour.obj. No layout or virtuals are modelled yet;
// base AI::cAgressiveResponsePilotBehaviour from CD2's inheritance registrar.
#ifndef AI_CCHASEANDATTACKPILOTBEHAVIOUR_H
#define AI_CCHASEANDATTACKPILOTBEHAVIOUR_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "gom/object_prototype.h"
#include "AI/cAgressiveResponsePilotBehaviour.h"

namespace AI
{
    class cChaseAndAttackPilotBehaviour : public cAgressiveResponsePilotBehaviour
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcChaseAndAttackPilotBehaviourClass;
    };
}

#endif // AI_CCHASEANDATTACKPILOTBEHAVIOUR_H
