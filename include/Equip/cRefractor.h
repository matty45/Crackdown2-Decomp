// CD2 constructor 0x826107F8 confirms the shared base constructor chain.
#include "Equip/cCWWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cRefractor (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x82610758) builds cClass(0x27415, "cRefractor", 0xA60); 0xA60 is the size its registrar gives.
#ifndef EQUIP_CREFRACTOR_H
#define EQUIP_CREFRACTOR_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cRefractor : public Equip::cCWWeapon
    {
    public:
        // CD2 factory 0x82610740 forwards only this, without a prototype argument.
        cRefractor();
        // CD2 0x826105E0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82610730: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCD710 names placement factory 0x82610740.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcRefractorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CREFRACTOR_H
