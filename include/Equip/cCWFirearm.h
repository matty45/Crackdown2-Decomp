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
        // CD2 table 0x820140A8 extends the inherited interface at these slots.
        virtual void vf410();
        virtual void vf411();
        virtual void vf412();

        // CD2 0x82617EB8: restores this class's vtables, then calls the base destructor (out of line: cUVTurret's calls it).
        virtual ~cCWFirearm();
        // Name and base from RuffKing. CD2: cCWFirearm::MakeNew (0x82617D50) allocates 0x6E0 and calls this constructor
        // (0x82618660), which calls cCWWeaponPrototype's (0x82608930).
        class cCWFirearmPrototype : public cCWWeapon::cCWWeaponPrototype
        {
        public:
            cCWFirearmPrototype(const RWS::CAttributePacket &);
            // CD2 own table 0x820056B0 differs from cCWWeaponPrototype here.
            virtual void HandleAttributes(const RWS::CAttributePacket &); // 1: 0x823728F8
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &); // 5: 0x82618768
            virtual unsigned int RetHeadShotKillPoints() const; // 23: 0x826164B8
            virtual unsigned int RetArmKillPoints() const; // 24: 0x826164C0
            virtual unsigned int RetLegKillPoints() const; // 25: 0x826164C8

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

        // CD2: cCWFirearm's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x82617F58
        virtual void Slot13(); // 13: 0x82617FB0
        virtual void Slot14(); // 14: 0x82618008
        virtual void Slot23(); // 23: 0x822DC738
        virtual void vf257(); // 257: 0x826181F8
        virtual void vf279(); // 279: 0x82399798
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x826164D0
    private:
        // CD2: cCWFirearm's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void ActivateLightAttachment(); // 338: 0x82618118
        virtual void DeactivateLightAttachment(); // 339: 0x82618178
        virtual bool IsLightAttachmentActive() const; // 340: 0x826181A0
        virtual void NotifyTracked(Equip::cEquipment *); // 341: 0x826181C8
    private:
        CD2_LAYOUT_CHECKS(cCWFirearm, CD2_SIZE(cCWFirearm, 0xAB0))

    public:
        // CD2 table 0x820140A8 differs from cCWWeapon at these inherited slots.
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // slot 18: 0x8263ACD0
    protected:
        virtual bool BeginAttack(); // slot 378: 0x82336D88
    public:
        virtual void vf407(); // slot 407: 0x823ABBE8
    protected:
        virtual void UpdateAttachedMuzzleEffect(); // slot 408: 0x826182E8
    };
}

#endif // EQUIP_CCWFIREARM_H
