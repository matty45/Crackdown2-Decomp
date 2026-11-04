#include "gom/object_prototype.h"
#ifndef AI_PEDESTRIANINJURED_H
#define AI_PEDESTRIANINJURED_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class PedestrianInjured : public cNonGameBase
    {
    public:
        // CD2 spawning initializer 0x82F932E8 names placement factory 0x824ab700.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pPedestrianInjuredClass;

        PedestrianInjured();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

