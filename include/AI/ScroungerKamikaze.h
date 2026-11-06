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
    };
}

#endif

