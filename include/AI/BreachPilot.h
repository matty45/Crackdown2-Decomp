#include "gom/object_prototype.h"
#ifndef AI_BREACHPILOT_H
#define AI_BREACHPILOT_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "AI/cPilotBase.h"

namespace AI
{
    class BreachPilot : public cPilotBase
    {
    public:
        // CD2 spawning initializer 0x82F9B2A0 names placement factory 0x824d16e0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pBreachPilotClass;

        BreachPilot();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8210C338 differs from cPilotBase at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824D18B0
        virtual void OnExit(); // slot 69: 0x824D1968
        virtual void Slot71(); // slot 71: 0x824D1A68
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824D19A8
        virtual void vf98(); // slot 98: 0x824D6BE8
        virtual void vf105(); // slot 105: 0x824D2670
        virtual void vf106(); // slot 106: 0x824D1AC0
        virtual void vf109(); // slot 109: 0x824D23D8
        virtual void vf110(); // slot 110: 0x824D2298
        virtual void vf113(); // slot 113: 0x824D1A10
        virtual void vf114(); // slot 114: 0x824D1A30
    };
}

#endif

