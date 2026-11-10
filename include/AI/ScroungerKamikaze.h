#include "gom/object_prototype.h"
#ifndef AI_SCROUNGERKAMIKAZE_H
#define AI_SCROUNGERKAMIKAZE_H

#include "gom/non_game_base.h"
#include "AI/Scrounger.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    // Base from CD2's inheritance registrar; the placement factory (0x824BDDF0) inlines this class's constructor over
    // Scrounger's (0x824BABB0).
    class ScroungerKamikaze : public AI::Scrounger
    {
    public:
        // CD2 spawning initializer 0x82F94800 names placement factory 0x824bddf0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pScroungerKamikazeClass;

        __forceinline ScroungerKamikaze() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        // CD2: ScroungerKamikaze's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void V104(); // 104: 0x824BE1D8
        virtual void V108(); // 108: 0x824BDF98
        virtual void Slot2(); // cSafeDeletable 2: 0x824BE218
    };
}

#endif

