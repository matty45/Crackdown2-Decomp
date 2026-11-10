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
        // CD2: cVehicleDamageProp's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x82732110
        virtual bool EnterPhysicalState(); // 7: 0x8224BF78
        virtual void Slot13(); // 13: 0x82732350
        virtual void Slot14(); // 14: 0x82732028
        virtual void Slot15(); // 15: 0x82730F50
        virtual void Slot23(); // 23: 0x82732358
        virtual void Slot24(); // 24: 0x82732458
        virtual void Slot64(); // 63: 0x82732148
        virtual void vf68(); // 68: 0x82732030
        virtual void vf92(); // 92: 0x82732A00
        virtual void vf147(); // 147: 0x82730BC0
        virtual void vf148(); // 148: 0x82730BB8
        virtual void vf156(); // 156: 0x8288F788
        virtual void vf271(); // 271: 0x82732200
        virtual void vf272(); // 272: 0x827322C0
        virtual void vf288(); // 288: 0x82732A18
        virtual void vf317(); // 317: 0x82731120
        virtual void vf327(); // 327: 0x82730BA0
        virtual void vf328(); // 328: 0x82730BA8
        virtual void vf329(); // 329: 0x82732460
        virtual void vf333(); // 333: 0x82732A90
        virtual void vf334(); // 334: 0x823872E0
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x82731D18
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x82731D20
    };
}

#endif // PROP_CVEHICLEDAMAGEPROP_H
