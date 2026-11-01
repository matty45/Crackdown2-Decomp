// AI::FreakBase (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824ABC68) is slot 11 of the vtable at 0x82109378, as cNonGameBase's RetClassName.
#ifndef AI_FREAKBASE_H
#define AI_FREAKBASE_H

#include "AI/cChaseBehaviour.h"
#include "gom/object_prototype.h"

namespace AI
{
    class FreakBase : public AI::NPCBehaviourSM
    {
    public:
        FreakBase();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pFreakBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    };
}

#endif // AI_FREAKBASE_H
