#include "gom/object_prototype.h"
#ifndef AI_PEDESTRIANINJURED_H
#define AI_PEDESTRIANINJURED_H

#include "gom/non_game_base.h"
#include "AI/PedestrianGuard.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    // Base from CD2's inheritance registrar; the placement factory (0x824AB700) inlines this class's constructor over
    // PedestrianGuard's (0x824AB1E0).
    class PedestrianInjured : public AI::PedestrianGuard
    {
    public:
        // CD2 spawning initializer 0x82F932E8 names placement factory 0x824ab700.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pPedestrianInjuredClass;

        __forceinline PedestrianInjured() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8200B038 differs from PedestrianGuard at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824AB8A8
        virtual void vf98(); // slot 98: 0x824AB980
        virtual void vf99(); // slot 99: 0x824AB998
    };
}

#endif

