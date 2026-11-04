// CD2 constructor 0x821F0768 confirms the shared base constructor chain.
#include "Equip/cCWWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cCWFirearm (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x82617DD0) builds cClass(0x3E81, "cCWFirearm", 0xAB0); 0xAB0 is the size its registrar gives.
#ifndef EQUIP_CCWFIREARM_H
#define EQUIP_CCWFIREARM_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cCWFirearm : public Equip::cCWWeapon
    {
    public:
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cCWFirearmPrototype : public cCWWeapon::cCWWeaponPrototype {};

        // CD2 factory 0x82617DB8 forwards only this, without a prototype argument.
        cCWFirearm();
        // CD2 0x82617DA8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCEA40 names placement factory 0x82617db8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCWFirearmClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // EQUIP_CCWFIREARM_H
