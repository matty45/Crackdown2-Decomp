// AI::Pedestrian (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824A8CC0) calls cPedestrianBase's constructor
// (0x824A91F8) and then installs Pedestrian's five vtables (0x82108DB0 at 0; 0x82108FA0, whose slot 1 is IsA, at 0x30):
// a cPedestrianBase with no fields of its own (both registrars give 0x120 bytes).
#ifndef AI_PEDESTRIAN_H
#define AI_PEDESTRIAN_H

#include "AI/cPedestrianBase.h"
#include "fun_runtime/class.h"
#include "cd2/layout.h"

namespace AI
{
    class Pedestrian : public cPedestrianBase
    {
    public:
        // CD2 table 0x82108DB0 has 112 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void vf111(); // primary slot 111

        static Fun_Runtime::cClass &StaticCreateClass();
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype, which this compiler does only when forced
        // (docs/matching-notes.md, "Inlining").
        __forceinline Pedestrian() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pPedestrianClass;

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(Pedestrian,
            CD2_SIZE(Pedestrian, 0x120))

    public:
        // CD2 table 0x82108DB0 differs from cPedestrianBase at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824A8F30
        virtual void OnExit(); // slot 69: 0x824A8F38
        virtual void Slot71(); // slot 71: 0x824A8FE8
        virtual void Slot79(); // slot 79: 0x824AB478
        virtual void vf98(); // slot 98: 0x824A8F40
        virtual void vf99(); // slot 99: 0x824A8F48
        virtual void vf100(); // slot 100: 0x824A8F50
    };
}

#endif
