#include "gom/object_prototype.h"
// Base cVehicleDamageProp: CD2's inheritance registrar names it, and the destructor 0x82730E98 calls cVehicleDamageProp's
// (0x8234EC90). Derived storage is not modelled.
#ifndef unknown_cTransVehicleDamageProp_H
#define unknown_cTransVehicleDamageProp_H

#include "Prop/cVehicleDamageProp.h"

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace unknown
{
    class cTransVehicleDamageProp : public Prop::cVehicleDamageProp
    {
    public:
        // Prototype name ours. CD2's MakeNew (0x82730C38) allocates 0x4F0, calls cPropPrototype's constructor
        // (0x8272D390) and stores this class's vptrs: this and cVehicleDamagePropPrototype's constructors are inline,
        // no fields.
        class cTransVehicleDamagePropPrototype : public Prop::cVehicleDamageProp::cVehicleDamagePropPrototype
        {
        public:
            __forceinline cTransVehicleDamagePropPrototype(const RWS::CAttributePacket &packet)
                : Prop::cVehicleDamageProp::cVehicleDamagePropPrototype(packet) {}

            // CD2: cTransVehicleDamagePropPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82731CC0
        public:
            CD2_LAYOUT_CHECKS(cTransVehicleDamagePropPrototype,
                CD2_SIZE(cTransVehicleDamagePropPrototype, 0x4F0))
        };

        // CD2 0x82730D78, called by the placement factory 0x82730CB8.
        cTransVehicleDamageProp(GOM::cObjectPrototype *);
        // CD2 0x82730E98.
        virtual ~cTransVehicleDamageProp();
        // CD2 spawning initializer 0x82FF5B30 names placement factory 0x82730cb8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcTransVehicleDamagePropClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    public:
        // CD2 table 0x8200EFD0 differs from cVehicleDamageProp at these inherited slots.
        virtual void Slot15(); // slot 15: 0x82730F50
        virtual void vf317(); // slot 317: 0x82731120
    };
}

#endif
