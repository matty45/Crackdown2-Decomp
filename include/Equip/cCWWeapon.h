#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cCWWeapon (Crackdown 2): STAND-IN: shared bases recovered; unmodelled instance fields remain opaque.
// StaticCreateClass (0x82607C30) builds cClass(0x3E82, "cCWWeapon", 0xA10); 0xA10 is the size its registrar gives.
#ifndef EQUIP_CCWWEAPON_H
#define EQUIP_CCWWEAPON_H

#include "fun_runtime/class.h"
#include "Equip/cWeapon.h"
#include "fun_runtime/stringc.h"
#include "fun_runtime/randgen.h"
namespace Vehicle { class cPintleMount; }

namespace Equip
{
    class cCWWeapon : public cWeapon
    {
    public:
        // CD2 table 0x820133D0 extends the inherited interface at these slots.
        virtual void vf406();
        virtual void vf407();
    protected:
        // Reference method/order; CD2 slot 408 is forwarded by PostAnimUpdate.
        virtual void UpdateAttachedMuzzleEffect();
        // Reference static randomizer. CD2's burst-pause consumer 0x8222B5D0
        // advances the two-word generator at 0x838389A0; its initializer follows
        // this object's script registrar (0x82FCB930).
        static Fun_Runtime::cRandGen ms_Randomiser;
    public:
        virtual void NotifyAttackComplete();

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
            // CD2 0x82608A48 destroys the audio-type string, then cWeaponPrototype.
            virtual ~cCWWeaponPrototype();

        private:
            friend class cCWWeapon;
            // Reference name/type; constructor and destructor establish the
            // 28-byte string at +0x350, including its 15-character small buffer.
            Fun_Runtime::cStringc m_strWeaponAudioType;
            unsigned char m_unmodelled36C[8];
            // Reference names; CD2 primary slot 315 and slots 326..329 read
            // these members at the offsets checked below.
            int m_nNumHands;
            unsigned char m_unmodelled378[4];
            // RevertAIAccuracyCone (0x82608788) reads this reference-named default.
            float m_fAIAccuracyCone;
            unsigned char m_unmodelled380[0x3AC - 0x380];
            int m_nUpperAimIndex;
            int m_nUpperReloadIndex;
            int m_nUpperFireIndex;
            int m_nUpperEquipIndex;
            unsigned char m_unmodelled3BC[4];
            // Reference level-one through level-five reload times. CD2's
            // RetReloadDuration indexes from +0x3C0 with firearm level minus one.
            float m_fReloadTime[5];
            unsigned char m_unmodelled3D4[4];

        public:
            // RuffKing's inline accessor; cCWWeapon::IsTurretWeapon (0x82607C10) reads the flag through it.
            bool IsTurretWeapon() const { return m_bTurret; }

        private:
            bool m_bTurret; // RuffKing name (its 0x3A8); CD2 reads 0x3D8
            unsigned char m_unmodelled3D9[0x3E0 - 0x3D9];

            // CD2: cCWWeaponPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82608AE0
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &); // 5: 0x82609260
            // Former scaffold attribution: HandleAttributes slot 1 was listed as
            // 0x8263BDB8, and kill-point slots 23..25 as 0x826164B8/0x826164C0/0x826164C8.
            // Reconstruction update: own table 0x8211F278 inherits the three
            // return-zero kill-point methods; cCWFirearmPrototype first overrides them.
        private:
            CD2_LAYOUT_CHECKS(cCWWeaponPrototype,
                CD2_SIZE(cCWWeaponPrototype, 0x3E0)
                CD2_OFFSET(cCWWeaponPrototype, m_strWeaponAudioType, 0x350)
                CD2_OFFSET(cCWWeaponPrototype, m_nNumHands, 0x374)
                CD2_OFFSET(cCWWeaponPrototype, m_fAIAccuracyCone, 0x37C)
                CD2_OFFSET(cCWWeaponPrototype, m_nUpperAimIndex, 0x3AC)
                CD2_OFFSET(cCWWeaponPrototype, m_nUpperReloadIndex, 0x3B0)
                CD2_OFFSET(cCWWeaponPrototype, m_nUpperFireIndex, 0x3B4)
                CD2_OFFSET(cCWWeaponPrototype, m_nUpperEquipIndex, 0x3B8)
                CD2_OFFSET(cCWWeaponPrototype, m_fReloadTime, 0x3C0)
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
        // Reference setters; CD2 0x82608768..0x82608798 writes the same fields
        // as the script-named getters above and restores the prototype default.
        void SetAIAccuracyCone(float);
        void SetAIInitialAccuracyCone(float);
        void SetAIPathClearCone(float);
        void SetAINumberOfShotsToFullAccuracy(unsigned int);
        void RevertAIAccuracyCone();
        void ResetNumberOfShotsTaken();
        // Reference member; CanAttack (0x82608440) reads the mount immediately
        // before the turret pointer, at +0x8EC in CD2.
        Vehicle::cPintleMount *RetPintleMount() { return m_pPintleMount; }
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
        unsigned char m_unmodelled8D8[0x8EC - 0x8D8];
        Vehicle::cPintleMount *m_pPintleMount;
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
            CD2_OFFSET(cCWWeapon, m_pPintleMount, 0x8EC)
            CD2_OFFSET(cCWWeapon, m_pTurret, 0x8F0))

    public:
        // CD2 table 0x820133D0 differs from cWeapon at these inherited slots.
        // First override owner: cEquipment retains 0x82604D68 and empty slots
        // 258..262, whereas this table installs the following CW weapon bodies.
        virtual Fun_Runtime::RetVal Term(); // slot 6: 0x82608200
        virtual void vf258(); // slot 258: 0x82608838
        virtual void vf259(); // slot 259: 0x82608850
        virtual void vf260(); // slot 260: 0x82608868
        virtual void vf261(); // slot 261: 0x82608880
        virtual void vf262(); // slot 262: 0x826088D8
        virtual void vf140(); // slot 140: 0x8234A320
        virtual void SetStatus(EQUIP_STATUS); // slot 316: 0x82237160
        virtual void vf366(); // slot 366: 0x82608300
        virtual void InitMaxAmmo(); // slot 367: 0x823789C8
    protected:
        virtual bool BeginAttack(); // slot 378: 0x8227C820
        virtual void EndAttack(); // slot 380: 0x82225C50
    protected:
        virtual bool CanAttack(); // slot 381: 0x82608440
    public:
        virtual float RetAttackDuration() const; // slot 383: 0x8263B7E8
    protected:
        virtual void EndReloading(); // slot 388: 0x823478E0
    public:
        virtual float RetReloadDuration() const; // slot 401: 0x82608560
        virtual void vf405(); // slot 405: 0x826087E8
    };
}

#endif // EQUIP_CCWWEAPON_H
