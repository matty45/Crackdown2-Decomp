#include "fun_runtime/class.h"
#include "rws/attributes.h"
// Prop::cVehicleDamageProp (Crackdown 2): STAND-IN for the class name only. Base Prop::cProp, as in RuffKing's header;
// RetClassName (0x82731E10) is slot 11 of the vtable at 0x82011120, as cNonGameBase's RetClassName.
#ifndef PROP_CVEHICLEDAMAGEPROP_H
#define PROP_CVEHICLEDAMAGEPROP_H

#include "Prop/cProp.h"

namespace Prop
{
    class cVehicleDamageProp : public Prop::cProp
    {
    public:
        static const Fun_Runtime::cClass *ms_pcVehicleDamagePropClass;
        // CD2 0x8234EC90: restores this class's vtables (primary 0x82011120), then calls cProp's destructor.
        virtual ~cVehicleDamageProp();
        // CD2 0x8232A5E8 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 placement factory 0x82731E20 tail-calls constructor 0x82731E40.
        cVehicleDamageProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing name and base; CD2 MakeNew (0x82731DA0) allocates 0x4F0 and adds no fields.
        class cVehicleDamagePropPrototype : public cProp::cPropPrototype
        {
        public:
            cVehicleDamagePropPrototype(const RWS::CAttributePacket &packet) : cPropPrototype(packet) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            virtual void HandleAttributes(const RWS::CAttributePacket &);

            CD2_LAYOUT_CHECKS(cVehicleDamagePropPrototype,
                CD2_SIZE(cVehicleDamagePropPrototype, 0x4F0))
        };
        virtual const char *RetClassName() const;
    };
}

#endif // PROP_CVEHICLEDAMAGEPROP_H
