// AI::cAgressiveResponsePilotBehaviour (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x824D0C00, MakeNew 0x824D2850, SpawnFromPrototype 0x824D0B78, from its registrars in CD2's
// initializer run); RuffKing names the class in AgressiveResponsePilotBehaviour.obj. No layout or virtuals are modelled yet;
// base AI::cAgressiveResponseBase from CD2's inheritance registrar.
#ifndef AI_CAGRESSIVERESPONSEPILOTBEHAVIOUR_H
#define AI_CAGRESSIVERESPONSEPILOTBEHAVIOUR_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "gom/object_prototype.h"
#include "AI/cAgressiveResponseBase.h"

namespace AI
{
    class cAgressiveResponsePilotBehaviour : public cAgressiveResponseBase
    {
    public:
        // CD2 placement factory tail-calls this constructor at 0x824D0CA8.
        cAgressiveResponsePilotBehaviour();
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgressiveResponsePilotBehaviourClass;
    };
}

#endif // AI_CAGRESSIVERESPONSEPILOTBEHAVIOUR_H
