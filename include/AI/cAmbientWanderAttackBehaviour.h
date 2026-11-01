#ifndef AI_cAmbientWanderAttackBehaviour_H
#define AI_cAmbientWanderAttackBehaviour_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class cAmbientWanderAttackBehaviour : public RWS::CAttributeHandler
    {
    public:
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pcAmbientWanderAttackBehaviourClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
