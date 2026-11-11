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
        // CD2 table 0x820133D0 extends the inherited interface at these slots.
        virtual void vf406();
        virtual void vf407();
        virtual void vf408();
        virtual void vf409();

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

            // CD2: cCWWeaponPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8263BDB8
            virtual unsigned int RetHeadShotKillPoints() const; // 23: 0x826164B8
            virtual unsigned int RetArmKillPoints() const; // 24: 0x826164C0
            virtual unsigned int RetLegKillPoints() const; // 25: 0x826164C8
        private:
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
        // CD2: cCWWeapon's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot13(); // 13: 0x82630028
        virtual void Slot14(); // 14: 0x826082A0
        virtual void Slot23(); // 23: 0x822AD100
        virtual void Slot61(); // 60: 0x826086B8
        virtual void vf257(); // 257: 0x8226CA68
        virtual void vf278(); // 278: 0x823AF810
        virtual int RetNumHands() const; // 315: 0x82608550
        virtual void TriggerReloadAudio(); // 319: 0x826084D0
        virtual void SetTurretMounted(Prop::cTurretBase *); // 321: 0x826085F8
    private:
        // CD2: cCWWeapon's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void PostAnimUpdate(float); // 324: 0x826084C0
        virtual int RetUpperAimIndex() const; // 326: 0x826087A8
        virtual int RetUpperReloadIndex() const; // 327: 0x826087B8
        virtual int RetUpperFireIndex() const; // 328: 0x826087C8
        virtual int RetUpperEquipIndex() const; // 329: 0x826087D8
    private:
        CD2_LAYOUT_CHECKS(cCWWeapon,
            CD2_SIZE(cCWWeapon, 0xA10)
            CD2_OFFSET(cCWWeapon, m_fAIAccuracyCone, 0x8C4)
            CD2_OFFSET(cCWWeapon, m_fAIPathClearCone, 0x8C8)
            CD2_OFFSET(cCWWeapon, m_fAIInitialAccuracyCone, 0x8CC)
            CD2_OFFSET(cCWWeapon, m_uiAINumberOfShotsToReachFullAccuracy, 0x8D0)
            CD2_OFFSET(cCWWeapon, m_uiShotCount, 0x8D4)
            CD2_OFFSET(cCWWeapon, m_pTurret, 0x8F0))

    public:
        // CD2 table 0x820133D0 differs from cWeapon at these inherited slots.
        virtual void vf140(); // slot 140: 0x8234A320
        virtual void SetStatus(EQUIP_STATUS); // slot 316: 0x82237160
        virtual void vf366(); // slot 366: 0x82608300
        virtual void vf367(); // slot 367: 0x823789C8
        virtual void vf378(); // slot 378: 0x8227C820
        virtual void vf380(); // slot 380: 0x82225C50
        virtual void vf381(); // slot 381: 0x82608440
        virtual void vf383(); // slot 383: 0x8263B7E8
        virtual void vf388(); // slot 388: 0x823478E0
        virtual void vf401(); // slot 401: 0x82608560
        virtual void vf405(); // slot 405: 0x826087E8
    };
}

#endif // EQUIP_CCWWEAPON_H
