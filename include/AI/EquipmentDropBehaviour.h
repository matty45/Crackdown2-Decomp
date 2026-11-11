#include "gom/object_prototype.h"
#ifndef AI_EQUIPMENTDROPBEHAVIOUR_H
#define AI_EQUIPMENTDROPBEHAVIOUR_H

#include "gom/non_game_base.h"
#include "AI/cPilotBase.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    // Base from CD2's inheritance registrar; the placement factory (0x824D2B60) inlines this class's constructor over
    // cPilotBase's (0x824D32E0).
    class EquipmentDropBehaviour : public AI::cPilotBase
    {
    public:
        // CD2 spawning initializer 0x82F9BA00 names placement factory 0x824d2b60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pEquipmentDropBehaviourClass;

        __forceinline EquipmentDropBehaviour() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8210C7D8 differs from cPilotBase at these inherited slots.
        virtual void OnExit(); // slot 69: 0x824C7978
        virtual void Slot79(); // slot 79: 0x824D2D08
        virtual void vf98(); // slot 98: 0x824D6BE8
        virtual void vf100(); // slot 100: 0x824D2FD8
        virtual void vf104(); // slot 104: 0x824D3090
        virtual void vf110(); // slot 110: 0x824D2F10
        virtual void vf111(); // slot 111: 0x824D2E20
        virtual void vf113(); // slot 113: 0x824D2E18
    };
}

#endif

