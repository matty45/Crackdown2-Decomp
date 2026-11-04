#ifndef AI_Squad_H
#define AI_Squad_H

#include "cd2/layout.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace AI
{
    class Squad : public RWS::CAttributeHandler
    {
    public:
        // CD2 MakeNew (0x824d81a0) allocates 0x70 bytes, calls GOM::cObjectPrototype's constructor (0x82654118) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class SquadPrototype : public GOM::cObjectPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline SquadPrototype(const RWS::CAttributePacket &packet) : GOM::cObjectPrototype(packet) {}

            CD2_LAYOUT_CHECKS(SquadPrototype, CD2_SIZE(SquadPrototype, 0x70))
        };

        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pSquadClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        Squad();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
