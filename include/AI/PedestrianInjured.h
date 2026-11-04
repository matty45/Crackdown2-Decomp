// AI::PedestrianInjured (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824AB700) calls PedestrianGuard's constructor (0x824AB1E0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_PEDESTRIANINJURED_H
#define AI_PEDESTRIANINJURED_H

#include "AI/PedestrianGuard.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class PedestrianInjured : public PedestrianGuard
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pPedestrianInjuredClass;

    private:

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline PedestrianInjured() {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(PedestrianInjured,
            CD2_SIZE(PedestrianInjured, 0x130))
    };
}

#endif

