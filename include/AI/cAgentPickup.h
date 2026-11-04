#include "gom/object_prototype.h"
#ifndef AI_CAGENTPICKUP_H
#define AI_CAGENTPICKUP_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cAgentPickup : public cNonGameBase
    {
    public:
        // CD2 spawning initializer 0x82F9AA30 names placement factory 0x824d0018.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcAgentPickupClass;

        cAgentPickup();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

