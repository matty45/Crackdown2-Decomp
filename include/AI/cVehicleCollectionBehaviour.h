#include "gom/object_prototype.h"
#ifndef AI_CVEHICLECOLLECTIONBEHAVIOUR_H
#define AI_CVEHICLECOLLECTIONBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cPilotBase.h"

namespace AI
{
    class cVehicleCollectionBehaviour : public cPilotBase
    {
    public:
        // CD2 spawning initializer 0x82F9CF18 names placement factory 0x824d68b8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcVehicleCollectionBehaviourClass;

        cVehicleCollectionBehaviour();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: cVehicleCollectionBehaviour's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824D7920
    };
}

#endif

