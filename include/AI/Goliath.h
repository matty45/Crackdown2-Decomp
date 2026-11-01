#include "rws/attributes.h"
// AI::Goliath (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824B0F18) is slot 11 of the vtable at 0x821096A0, as cNonGameBase's RetClassName.
#ifndef AI_GOLIATH_H
#define AI_GOLIATH_H

#include "AI/cChaseBehaviour.h"

namespace AI
{
    class Goliath : public AI::NPCBehaviourSM
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pGoliathClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_GOLIATH_H
