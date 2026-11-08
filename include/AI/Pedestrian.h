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
    };
}

#endif
