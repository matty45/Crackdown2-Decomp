#include "Equip/cCWHeavyWeapon.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cFlocketLauncher (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cCWHeavyWeapon: CD2's inheritance registrar names it, and the destructor 0x82630FF0 calls cCWHeavyWeapon's (0x8262FCB0).
// StaticCreateClass (0x82630F08) builds cClass(0x605F, "cFlocketLauncher", 0xA30); 0xA30 is the size its registrar gives.
#ifndef EQUIP_CFLOCKETLAUNCHER_H
#define EQUIP_CFLOCKETLAUNCHER_H

#include "fun_runtime/class.h"

namespace Equip
{
    class cFlocketLauncher : public cCWHeavyWeapon
    {
    public:
        // Inline: CD2's placement factory (0x82630E30) calls cCWHeavyWeapon's constructor (0x8262FF78), then stores this
        // class's vptrs and clears the two fields below (RuffKing's names; 0xB0 lower in CD2).
        __forceinline cFlocketLauncher() : m_fAttackTime(0.0f), m_nBarrelID(0) {}
        // CD2 0x82630CF0: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82630D00: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // CD2 0x82630FF0.
        virtual ~cFlocketLauncher();
        // CD2 0x82630E20: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FD33B0 names placement factory 0x82630e30.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcFlocketLauncherClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        float m_fAttackTime;                        // 0xA20
        unsigned char m_nBarrelID;                  // 0xA24
        unsigned char m_unmodelledA25[0xA30 - 0xA25];

        CD2_LAYOUT_CHECKS(cFlocketLauncher,
            CD2_SIZE(cFlocketLauncher, 0xA30)
            CD2_OFFSET(cFlocketLauncher, m_fAttackTime, 0xA20)
            CD2_OFFSET(cFlocketLauncher, m_nBarrelID, 0xA24))
    };
}

#endif // EQUIP_CFLOCKETLAUNCHER_H
