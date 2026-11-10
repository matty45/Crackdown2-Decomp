#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cEquipment (Crackdown 2): STAND-IN: shared bases recovered; unmodelled instance fields remain opaque.
// StaticCreateClass (0x82604750) builds cClass(0x6, "cEquipment", 0x870); 0x870 is the size its registrar gives.
#ifndef EQUIP_CEQUIPMENT_H
#define EQUIP_CEQUIPMENT_H

#include "fun_runtime/class.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "fun_runtime/cStateMachine.h"

namespace Prop { class cTurretBase; }

namespace Equip
{
    class cEquipment : public PHYSICS::cNetDynamicBody, public Fun_Runtime::cStateMachine
    {
    public:
        // CD2 0x826046D0: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x82604CA8 (out of line: cWeaponProjectile's destructor 0x826096C0 calls it).
        virtual ~cEquipment();
        // RuffKing's EQUIP_STATUS (SetStatus's parameter).
        enum EQUIP_STATUS
        {
            STATUS_UNDEFINDED = 0,
            STATUS_FREE,
            STATUS_STORED,
            STATUS_EQUIPPED,
            STATUS_MOUNTED
        };
        // Own primary slots from 314 (table 0x82010000 has 363 entries; cNetDynamicBody ends at 313). Names and order
        // are RuffKing's (its slots 279..288); CD2's bodies agree: 315/317 return 1, 319/321 are empty, 322/323 return
        // 0 here, and cCWWeapon's 321/322 (0x826085F8/0x82607C08) set and return the turret pointer at 0x8F0.
        virtual void ResetHavokPhysics();                       // 314
        virtual int RetNumHands() const;                        // 315
        virtual void SetStatus(EQUIP_STATUS);                   // 316
        virtual bool ShouldBeForceStored();                     // 317
        virtual bool Activate();                                // 318
        virtual void TriggerReloadAudio();                      // 319
        virtual unsigned int RetWeaponPriority() const;         // 320
        virtual void SetTurretMounted(Prop::cTurretBase *);     // 321
        virtual Prop::cTurretBase *RetTurretMounted() const;    // 322
        virtual bool IsTurretWeapon() const;                    // 323
        // Name and base from RuffKing. CD2: cEquipment::MakeNew (0x82604650) allocates 0x2F0 and calls this constructor
        // (0x826071F8), which calls cDynamicBodyPrototype's (0x82686DD8).
        class cEquipmentPrototype : public PHYSICS::cDynamicBody::cDynamicBodyPrototype
        {
        public:
            cEquipmentPrototype(const RWS::CAttributePacket &);
            // CD2 0x82607328 (out of line: cWeaponProjectilePrototype's deleting destructor calls it).
            virtual ~cEquipmentPrototype();
            // Prototype table slots 14..25 (0x8211EED8; slots 11..13 come from the body prototypes, which do not
            // declare them yet). Names, order and fields are RuffKing's, one slot later there; the getters read
            // RuffKing's offsets except the two pickup-VFX IDs, which are 4 bytes higher in CD2.
            virtual float RetDroppedDeletionTime() const;       // 14
            virtual float RetPickupDeletionTime() const;        // 15 (folded: 0x825EC2E8)
            virtual bool CanZoom() const;                       // 16
            virtual float RetMaxZoomFactor() const;             // 17
            virtual float RetZoomSpeed() const;                 // 18
            virtual int RetInInvPickupVFXID() const;            // 19
            virtual int RetNotInInvPickupVFXID() const;         // 20
            virtual bool RetLoadedCmdSpawn() const;             // 21
            virtual unsigned int RetPvPKillPoints() const;      // 22
            virtual unsigned int RetHeadShotKillPoints() const; // 23
            virtual unsigned int RetArmKillPoints() const;      // 24
            virtual unsigned int RetLegKillPoints() const;      // 25

        protected:
            float m_fDroppedDeletionTime;   // 0x280
            float m_fPickupDeletionTime;    // 0x284
            float m_fMaxZoomFactor;         // 0x288
            float m_fZoomSpeed;             // 0x28C
            bool m_bCanZoom;                // 0x290
            bool m_bScale;                  // 0x291
            bool m_bLoadedCmdSpawn;         // 0x292

        private:
            unsigned char m_unmodelled293[0x2C4 - 0x293];

        protected:
            int m_nInInvPickupId;           // 0x2C4
            int m_nNotInInvPickupId;        // 0x2C8

        private:
            unsigned char m_unmodelled2CC[0x2F0 - 0x2CC];

            CD2_LAYOUT_CHECKS(cEquipmentPrototype,
                CD2_SIZE(cEquipmentPrototype, 0x2F0)
                CD2_OFFSET(cEquipmentPrototype, m_fDroppedDeletionTime, 0x280)
                CD2_OFFSET(cEquipmentPrototype, m_fMaxZoomFactor, 0x288)
                CD2_OFFSET(cEquipmentPrototype, m_bCanZoom, 0x290)
                CD2_OFFSET(cEquipmentPrototype, m_bLoadedCmdSpawn, 0x292)
                CD2_OFFSET(cEquipmentPrototype, m_nInInvPickupId, 0x2C4)
                CD2_OFFSET(cEquipmentPrototype, m_nNotInInvPickupId, 0x2C8))
        };

        // CD2 placement factory forwards only this; later reference builds add a prototype argument.
        cEquipment();
        // CD2 0x826046A8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCB2A0 names placement factory 0x826046b8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcEquipmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    private:
        // CD2 constructor 0x82604AF8: reference hierarchy, descriptor size 0x870.
        unsigned char m_unmodelled7A4[0x870 - 0x7A4];
        CD2_LAYOUT_CHECKS(cEquipment, CD2_SIZE(cEquipment, 0x870))
    };
}

#endif // EQUIP_CEQUIPMENT_H
