// CD2 constructor 0x824D8370 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "gom/non_game_base.h"
#include "gom/object_prototype.h"
#ifndef AI_Squad_H
#define AI_Squad_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class Squad : public cNonGameBase
    {
    public:
        // CD2 factory 0x824D8220 forwards only this, without a prototype argument.
        Squad();
        // CD2 spawning initializer 0x82F9D350 names placement factory 0x824d8220.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pSquadClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
