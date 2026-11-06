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
        // CD2 0x82617EB8: restores this class's vtables, then calls the base destructor (out of line: cUVTurret's calls it).
        virtual ~cCWFirearm();
        // Name and base from RuffKing. CD2: cCWFirearm::MakeNew (0x82617D50) allocates 0x6E0 and calls this constructor
        // (0x82618660), which calls cCWWeaponPrototype's (0x82608930).
        class cCWFirearmPrototype : public cCWWeapon::cCWWeaponPrototype
        {
        public:
            cCWFirearmPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled3E0[0x6E0 - 0x3E0];

            CD2_LAYOUT_CHECKS(cCWFirearmPrototype,
                CD2_SIZE(cCWFirearmPrototype, 0x6E0))
        };

        // CD2 factory 0x82617DB8 forwards only this, without a prototype argument.
        cCWFirearm();
        // CD2 0x82617DA8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCEA40 names placement factory 0x82617db8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCWFirearmClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        // Own fields not recovered; 0xAB0 is the size its class-factory registrar gives (derived classes start there).
        unsigned char m_unmodelledA10[0xAB0 - 0xA10];

        CD2_LAYOUT_CHECKS(cCWFirearm, CD2_SIZE(cCWFirearm, 0xAB0))
    };
}

#endif // EQUIP_CCWFIREARM_H
