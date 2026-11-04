#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cCWWeapon (Crackdown 2): STAND-IN: shared bases recovered; unmodelled instance fields remain opaque.
// StaticCreateClass (0x82607C30) builds cClass(0x3E82, "cCWWeapon", 0xA10); 0xA10 is the size its registrar gives.
#ifndef EQUIP_CCWWEAPON_H
#define EQUIP_CCWWEAPON_H

#include "fun_runtime/class.h"
#include "Equip/cWeapon.h"

namespace Equip
{
    class cCWWeapon : public cWeapon
    {
    public:
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        class cCWWeaponPrototype : public cWeapon::cWeaponPrototype {};

        // CD2 factory 0x82607BB8 forwards only this, without a prototype argument.
        cCWWeapon();
        // CD2 0x82607BA8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCB890 names placement factory 0x82607bb8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCWWeaponClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 constructor 0x82607FC8: reference hierarchy, descriptor size 0xA10.
        unsigned char m_unmodelled8C0[0xA10 - 0x8C0];
        CD2_LAYOUT_CHECKS(cCWWeapon, CD2_SIZE(cCWWeapon, 0xA10))
    };
}

#endif // EQUIP_CCWWEAPON_H
