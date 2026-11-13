// CD2 constructor 0x82635628 confirms the shared base constructor chain.
#include "Equip/cCWWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cSucknBlowGun (Crackdown 2): STAND-IN: constructor-confirmed base; remaining instance fields are not modelled.
// StaticCreateClass (0x82635588) builds cClass(0x27418, "cSucknBlowGun", 0xDF0); 0xDF0 is the size its registrar gives.
#ifndef UNKNOWN_CSUCKNBLOWGUN_H
#define UNKNOWN_CSUCKNBLOWGUN_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cSucknBlowGun : public Equip::cCWWeapon
    {
    public:
        // CD2 factory 0x82635558 forwards only this, without a prototype argument.
        cSucknBlowGun();
        // CD2 0x82635548: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 slot 390 (0x82638858) tail-calls cWeapon::InitiateReload.
        virtual bool InitiateReload();
        // CD2 spawning initializer 0x82FD3FB8 names placement factory 0x82635558.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcSucknBlowGunClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSUCKNBLOWGUN_H
