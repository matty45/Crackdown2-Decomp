#include "gom/object_prototype.h"
#ifndef AI_CAGENTPICKUP_H
#define AI_CAGENTPICKUP_H

#include "gom/non_game_base.h"
#include "AI/cPilotBase.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    // Base from CD2's inheritance registrar; the placement factory (0x824D0018) inlines this class's constructor over
    // cPilotBase's (0x824D32E0).
    class cAgentPickup : public AI::cPilotBase
    {
    public:
        // CD2 spawning initializer 0x82F9AA30 names placement factory 0x824d0018.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgentPickupClass;

        __forceinline cAgentPickup() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

