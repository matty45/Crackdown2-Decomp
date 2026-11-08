#include "gom/object_prototype.h"
#ifndef AI_CAGRESSIVERESPONSECHASEBEHAVIOUR_H
#define AI_CAGRESSIVERESPONSECHASEBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cAgressiveResponseBase.h"

namespace AI
{
    class cAgressiveResponseChaseBehaviour : public cAgressiveResponseBase
    {
    public:
        // CD2 spawning initializer 0x82F99518 names placement factory 0x824c92b0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgressiveResponseChaseBehaviourClass;

        cAgressiveResponseChaseBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

