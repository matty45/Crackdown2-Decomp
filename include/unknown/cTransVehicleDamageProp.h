#ifndef unknown_cTransVehicleDamageProp_H
#define unknown_cTransVehicleDamageProp_H

#include "cd2/layout.h"
#include "Prop/cProp.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cTransVehicleDamageProp : public RWS::CAttributeHandler
    {
    public:
        // CD2 MakeNew (0x82730c38) allocates 0x4F0 bytes, calls Prop::cProp::cPropPrototype's constructor (0x8272D390) with the packet and
        // installs this prototype's vtables (at 0 and 0x18).
        class cTransVehicleDamagePropPrototype : public Prop::cProp::cPropPrototype
        {
        public:
            // __forceinline: CD2 inlines this constructor into MakeNew (docs/matching-notes.md, "Inlining").
            __forceinline cTransVehicleDamagePropPrototype(const RWS::CAttributePacket &packet) : Prop::cProp::cPropPrototype(packet) {}

            CD2_LAYOUT_CHECKS(cTransVehicleDamagePropPrototype, CD2_SIZE(cTransVehicleDamagePropPrototype, 0x4F0))
        };

        // Out of line: CD2 tail-calls it from SpawnFromPrototype with the prototype.
        cTransVehicleDamageProp(GOM::cObjectPrototype *prototype);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static const Fun_Runtime::cClass *ms_pcTransVehicleDamagePropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
