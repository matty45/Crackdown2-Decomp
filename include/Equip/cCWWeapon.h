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
        // CD2 0x82607BD0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x82256348 (out of line: cCWHeavyWeapon's and cCWFirearm's destructors call it).
        virtual ~cCWWeapon();
        // Name and base from RuffKing. CD2: cCWWeapon::MakeNew (0x82607B50) allocates 0x3E0 and calls this constructor
        // (0x82608930), which calls cWeaponPrototype's (0x8260A370).
        class cCWWeaponPrototype : public cWeapon::cWeaponPrototype
        {
        public:
            cCWWeaponPrototype(const RWS::CAttributePacket &);

        private:
            unsigned char m_unmodelled350[0x3D8 - 0x350];

        public:
            // RuffKing's inline accessor; cCWWeapon::IsTurretWeapon (0x82607C10) reads the flag through it.
            bool IsTurretWeapon() const { return m_bTurret; }

        private:
            bool m_bTurret; // RuffKing name (its 0x3A8); CD2 reads 0x3D8
            unsigned char m_unmodelled3D9[0x3E0 - 0x3D9];

            CD2_LAYOUT_CHECKS(cCWWeaponPrototype,
                CD2_SIZE(cCWWeaponPrototype, 0x3E0)
                CD2_OFFSET(cCWWeaponPrototype, m_bTurret, 0x3D8))
        };

        // CD2 factory 0x82607BB8 forwards only this, without a prototype argument.
        cCWWeapon();
        // CD2 script registrations name these accessors; the reference names the fields.
        float RetAIAccuracyCone() const;
        float RetAIInitialAccuracyCone() const;
        float RetAIPathClearCone() const;
        unsigned int RetAINumberOfShotsToFullAccuracy() const;
        unsigned int RetNumberOfShotsTaken() const;
        // cEquipment slots 322/323 (CD2 0x82607C08, 0x82607C10).
        virtual Prop::cTurretBase *RetTurretMounted() const;
        virtual bool IsTurretWeapon() const;
        // CD2 0x82607BA8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCB890 names placement factory 0x82607bb8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcCWWeaponClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 constructor 0x82607FC8: reference hierarchy, descriptor size 0xA10.
        unsigned char m_unmodelled8C0[4];
    protected:
        float m_fAIAccuracyCone;
        float m_fAIPathClearCone;
        float m_fAIInitialAccuracyCone;
        unsigned int m_uiAINumberOfShotsToReachFullAccuracy;
        unsigned int m_uiShotCount;
    private:
        unsigned char m_unmodelled8D8[0x8F0 - 0x8D8];
    protected:
        Prop::cTurretBase *m_pTurret;   // RuffKing name; SetTurretMounted (0x826085F8) and RetTurretMounted use 0x8F0
    private:
        unsigned char m_unmodelled8F4[0xA10 - 0x8F4];
        CD2_LAYOUT_CHECKS(cCWWeapon,
            CD2_SIZE(cCWWeapon, 0xA10)
            CD2_OFFSET(cCWWeapon, m_fAIAccuracyCone, 0x8C4)
            CD2_OFFSET(cCWWeapon, m_fAIPathClearCone, 0x8C8)
            CD2_OFFSET(cCWWeapon, m_fAIInitialAccuracyCone, 0x8CC)
            CD2_OFFSET(cCWWeapon, m_uiAINumberOfShotsToReachFullAccuracy, 0x8D0)
            CD2_OFFSET(cCWWeapon, m_uiShotCount, 0x8D4)
            CD2_OFFSET(cCWWeapon, m_pTurret, 0x8F0))
    };
}

#endif // EQUIP_CCWWEAPON_H
