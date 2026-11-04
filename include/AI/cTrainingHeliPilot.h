#include "gom/object_prototype.h"
#ifndef AI_CTRAININGHELIPILOT_H
#define AI_CTRAININGHELIPILOT_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cTrainingHeliPilot : public cNonGameBase
    {
    public:
        // CD2 spawning initializer 0x82F9CAE0 names placement factory 0x824d5350.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTrainingHeliPilotClass;

        cTrainingHeliPilot();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

