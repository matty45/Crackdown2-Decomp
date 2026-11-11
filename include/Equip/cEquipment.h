#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Equip::cEquipment (Crackdown 2): STAND-IN: shared bases recovered; unmodelled instance fields remain opaque.
// StaticCreateClass (0x82604750) builds cClass(0x6, "cEquipment", 0x870); 0x870 is the size its registrar gives.
#ifndef EQUIP_CEQUIPMENT_H
#define EQUIP_CEQUIPMENT_H

#include "fun_runtime/class.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "fun_runtime/cStateMachine.h"
#include "fun_runtime/State.h"

namespace Prop { class cTurretBase; }
namespace Fun_Runtime { class State; class Mtx; class cString; class Vec3; }
namespace CHARACTER { class cCharacter; }

namespace Equip
{
    // Reference equipment enums; CD2 cEquipmentPrototype initializes category 5
    // and type 0, while cWeaponPrototype changes them to weapon (0), primary (1).
    enum eEquipmentType { eEquipT_None = 0, eEquipT_Primary, eEquipT_Secondary };
    enum EQUIP_CATEGORY
    {
        CATEGORY_WEAPON = 0, CATEGORY_MISC, CATEGORY_CLOTHING,
        CATEGORY_AMMUNITION, CATEGORY_END, CATEGORY_UNDEFINED
    };

    class cEquipment : public PHYSICS::cNetDynamicBody, public Fun_Runtime::cStateMachine
    {
    protected:
        // Shared reference base of cWeapon::STATE_Idle. These states have no
        // members beyond State's name pointer; CD2's derived state table has three slots.
        class STATE_Idle : public Fun_Runtime::State
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Idle, CD2_SIZE(STATE_Idle, 8))
        };
        // Reference active-state base has the same complete eight-byte State storage.
        class STATE_Active : public Fun_Runtime::State
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Active, CD2_SIZE(STATE_Active, 8))
        };
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
        // Slots 324 to 362: RuffKing's remaining cEquipment virtuals, in its order (its slots 289 to 327). CD2's
        // cWeaponProjectile, which adds one virtual, has 364 slots, and cHWProjectile's eleven end at 374 with
        // UpdateAttachedEffect and ReleaseEffect, as cFlocket's table has them. An overloaded pair is declared
        // non-const first: the compiler gives overloads their slots in reverse.
        virtual void PostAnimUpdate(float);                     // 324
        virtual bool GetVisibility();
        virtual int RetUpperAimIndex() const;
        virtual int RetUpperReloadIndex() const;
        virtual int RetUpperFireIndex() const;
        virtual int RetUpperEquipIndex() const;
        virtual bool IsLive();                                  // 330
        virtual bool IsDetonating();
        virtual unsigned int RetTotalAmmo() const;
        virtual bool HasMaxAmmo() const;
        virtual bool IsMarkedForDeletion();
        virtual bool PickUpRequested(cGameBase *pOwnerTest);    // 335
        virtual bool CanBeEquipped();
        virtual void ToggleLightAttachment();
        virtual void ActivateLightAttachment();
        virtual void DeactivateLightAttachment();
        virtual bool IsLightAttachmentActive() const;           // 340
        virtual void NotifyTracked(cEquipment *);
        virtual Fun_Runtime::Mtx *GetMatrix(Fun_Runtime::Mtx &Mat);
        virtual void CreateDynamicObstacle();
        virtual void DestroyDynamicObstacle();
        virtual bool CanSpawnPickupVFX();                       // 345
        virtual Fun_Runtime::cString GetNetDebugString();
        virtual bool CanForceNetTransform() const;
        virtual bool CanReleaseNetOwnershipOnAVExit() const;
        virtual bool CanReleaseNetOwnershipOnInitMsg() const;
        virtual int RetNetworkLOD(CHARACTER::cCharacter *pRelevantPlayer, int nNodeID);   // 350
        virtual Fun_Runtime::Vec3 RetReplicationVelocity();
        virtual void OnFailedOwnershipTransition();
        virtual bool CheckForOwnershipTransition();
        virtual bool CanDoOwnershipTransition();
        virtual Fun_Runtime::State *RetSTATE_Deactivated();     // 355/356
        virtual Fun_Runtime::State *RetSTATE_Deactivated() const;
        virtual Fun_Runtime::State *RetSTATE_Idle();            // 357/358
        virtual Fun_Runtime::State *RetSTATE_Idle() const;
        virtual Fun_Runtime::State *RetSTATE_Active();          // 359/360
        virtual Fun_Runtime::State *RetSTATE_Active() const;
        virtual Fun_Runtime::State *RetSTATE_Paused();          // 361/362
        virtual Fun_Runtime::State *RetSTATE_Paused() const;
        // Name and base from RuffKing. CD2: cEquipment::MakeNew (0x82604650) allocates 0x2F0 and calls this constructor
        // (0x826071F8), which calls cDynamicBodyPrototype's (0x82686DD8).
        class cEquipmentPrototype : public PHYSICS::cDynamicBody::cDynamicBodyPrototype
        {
        public:
            cEquipmentPrototype(const RWS::CAttributePacket &);
            // CD2 0x82607328 (out of line: cWeaponProjectilePrototype's deleting destructor calls it).
            virtual ~cEquipmentPrototype();
            // Reference owns this override; CD2 table 0x8211EED8 slot 1 is 0x826073B8.
            virtual void HandleAttributes(const RWS::CAttributePacket &);
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
            unsigned char m_unmodelled293[0x29C - 0x293];

        protected:
            EQUIP_CATEGORY m_EquipmentCategory; // CD2 constructor 0x826071F8: +0x29C, initially CATEGORY_UNDEFINED

        private:
            unsigned char m_unmodelled2A0[0x2C4 - 0x2A0];

        protected:
            int m_nInInvPickupId;           // 0x2C4
            int m_nNotInInvPickupId;        // 0x2C8
            eEquipmentType m_EquipmentType; // CD2 constructor 0x826071F8: +0x2CC, initially eEquipT_None

        private:
            unsigned char m_unmodelled2D0[0x2F0 - 0x2D0];

            // CD2: cEquipmentPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82607978
        private:
            CD2_LAYOUT_CHECKS(cEquipmentPrototype,
                CD2_SIZE(cEquipmentPrototype, 0x2F0)
                CD2_OFFSET(cEquipmentPrototype, m_fDroppedDeletionTime, 0x280)
                CD2_OFFSET(cEquipmentPrototype, m_fMaxZoomFactor, 0x288)
                CD2_OFFSET(cEquipmentPrototype, m_bCanZoom, 0x290)
                CD2_OFFSET(cEquipmentPrototype, m_bLoadedCmdSpawn, 0x292)
                CD2_OFFSET(cEquipmentPrototype, m_EquipmentCategory, 0x29C)
                CD2_OFFSET(cEquipmentPrototype, m_nInInvPickupId, 0x2C4)
                CD2_OFFSET(cEquipmentPrototype, m_nNotInInvPickupId, 0x2C8)
                CD2_OFFSET(cEquipmentPrototype, m_EquipmentType, 0x2CC))
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
        unsigned char m_unmodelled7A4[0x7E4 - 0x7A4];
    protected:
        // RuffKing m_fTimer follows equipment status. CD2 constructor 0x82604AF8
        // initializes it at +0x7E4; cWeapon::BeginAttack and both reload completions
        // write this same timer, independently of cWeapon's own attack timer.
        float m_fTimer;
    private:
        unsigned char m_unmodelled7E8[0x870 - 0x7E8];
        // CD2: cEquipment's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x82608200
        virtual void Slot13(); // 13: 0x8261E5D8
        virtual void Slot14(); // 14: 0x82685850
        virtual void Slot23(); // 23: 0x821D0F58
        virtual void Slot24(); // 24: 0x822C9E98
        virtual void UpdateRenderMatrix(); // 26: 0x822DD5A0
        virtual void LeaveRenderableState(); // 32: 0x82605B40
        virtual void Slot63(); // 62: 0x82605FD0
        virtual void Slot64(); // 63: 0x82605D20
        virtual void vf76(); // 76: 0x822E88B0
        virtual void vf86(); // 86: 0x826057A8
        virtual void vf87(); // 87: 0x826058A8
        virtual void vf91(); // 91: 0x82605710
        virtual void vf92(); // 92: 0x82605610
        virtual void vf122(); // 122: 0x82605008
        virtual void vf127(); // 127: 0x82605010
        virtual void vf153(); // 153: 0x82604F98
        virtual void vf154(); // 154: 0x82604FA0
        virtual void vf158(); // 158: 0x82689BF0
        virtual void vf168(); // 168: 0x822CDDC0
        virtual void vf244(); // 244: 0x8288FB78
        virtual void vf245(); // 245: 0x827E56A8
        virtual void vf254(); // 254: 0x822C5A30
        virtual void vf257(); // 257: 0x822312B0
        // virtual void vf258(); // 258: 0x82608838
        // virtual void vf259(); // 259: 0x82608850
        // virtual void vf260(); // 260: 0x82608868
        // virtual void vf261(); // 261: 0x82608880
        // virtual void vf262(); // 262: 0x826088D8
        // Reconstruction update: cEquipment table 0x82010000 slots 258..262
        // retain cDynamicBody's empty body 0x82580578. These former declarations
        // attributed later derived overrides to the equipment base.
        virtual void vf266(); // 266: 0x82686C98
        virtual void vf272(); // 272: 0x827454F8
        virtual void vf280(); // 280: 0x827E56A8
        virtual void vf281(); // 281: 0x8288FB78
        virtual void vf282(); // 282: 0x827E56A8
        virtual void vf284(); // 284: 0x82605CF0
        virtual void vf285(); // 285: 0x82605D08
        virtual void vf288(); // 288: 0x827E56A8
        virtual void vf295(); // 295: 0x82580578
        virtual void vf296(); // 296: 0x82580578
        virtual void vf304(); // 304: 0x82580578
        virtual void vf309(); // 309: 0x82580578
        virtual void vf310(); // 310: 0x827E56A8
        virtual void SetNetRole(etNetRole); // cNetRoleObject 1: 0x82606B80
        virtual void CalculateRelevancy(int); // cReplicatedClass 2: 0x825DEEE0
        virtual void CalculateLOD(int); // cReplicatedClass 3: 0x826066B0
        virtual bool CanSendTermPacketOnNotRelevant() const; // cReplicatedClass 4: 0x8288FB78
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8260A298
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x82205518
        virtual void ReplicateHeaderData(); // cReplicatedClass 10: 0x82605FE0
        virtual unsigned int GetNumObjectIDBits() const; // cReplicatedClass 16: 0x8288E558
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const; // cReplicatedClass 22: 0x8288CA00
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288E460
    protected:
        virtual void EventTriggerStartFire(CHARACTER::cCharacter *); // cIgnitable 10: 0x82580578
        virtual void EventTriggerEndFire(); // cIgnitable 12: 0x82580578
    private:
        CD2_LAYOUT_CHECKS(cEquipment,
            CD2_SIZE(cEquipment, 0x870)
            CD2_OFFSET(cEquipment, m_fTimer, 0x7E4))
    };
}

#endif // EQUIP_CEQUIPMENT_H
