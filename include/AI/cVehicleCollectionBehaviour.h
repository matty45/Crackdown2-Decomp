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
        // CD2 table 0x8210CEA0 has 117 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void vf115(); // primary slot 115
        virtual void vf116(); // primary slot 116

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

    public:
        // CD2 table 0x8210CEA0 differs from cPilotBase at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824D6B20
        virtual void OnExit(); // slot 69: 0x824C7978
        virtual void Slot71(); // slot 71: 0x824D1A68
        virtual void vf98(); // slot 98: 0x824D6BE8
        virtual void vf100(); // slot 100: 0x824D7728
        virtual void vf104(); // slot 104: 0x824D6DC0
        virtual void vf106(); // slot 106: 0x824D6DC8
        virtual void vf108(); // slot 108: 0x824D6F18
        virtual void vf109(); // slot 109: 0x824D70A8
        virtual void vf110(); // slot 110: 0x824D7260
        virtual void vf113(); // slot 113: 0x824D6BF0
    };
}

#endif

