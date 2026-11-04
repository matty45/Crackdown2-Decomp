// CD2 constructor 0x824CDEA8 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/cAmbientTrafficBehaviour.h"
#include "gom/object_prototype.h"
#ifndef AI_cAmbientWanderAttackBehaviour_H
#define AI_cAmbientWanderAttackBehaviour_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cAmbientWanderAttackBehaviour : public AI::cAmbientTrafficBehaviour
    {
    public:
        // CD2 factory 0x824CDD78 forwards only this, without a prototype argument.
        cAmbientWanderAttackBehaviour();
        // CD2 spawning initializer 0x82F99D88 names placement factory 0x824cdd78.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAmbientWanderAttackBehaviourClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
