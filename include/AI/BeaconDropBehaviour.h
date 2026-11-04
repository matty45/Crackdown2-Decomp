#include "gom/object_prototype.h"
#ifndef AI_BEACONDROPBEHAVIOUR_H
#define AI_BEACONDROPBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class BeaconDropBehaviour : public cNonGameBase
    {
    public:
        // CD2 spawning initializer 0x82F98000 names placement factory 0x824c77c8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pBeaconDropBehaviourClass;

        BeaconDropBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

