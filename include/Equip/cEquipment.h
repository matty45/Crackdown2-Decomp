#include "gom/object_prototype.h"
#include "gom/cPointOfInterest.h"
#include "rws/attributes.h"
// Equip::cEquipment (Crackdown 2): STAND-IN: shared bases recovered; unmodelled instance fields remain opaque.
// StaticCreateClass (0x82604750) builds cClass(0x6, "cEquipment", 0x870); 0x870 is the size its registrar gives.
#ifndef EQUIP_CEQUIPMENT_H
#define EQUIP_CEQUIPMENT_H

#include "fun_runtime/class.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "fun_runtime/cStateMachine.h"
#include "fun_runtime/State.h"
#include "fun_runtime/mtx.h"

namespace Prop { class cTurretBase; }
namespace Fun_Runtime { class State; class Mtx; class cString; class Vec3; }
namespace CHARACTER { class cCharacter; }
namespace VFX { class cParticleEffectInstance; }
namespace GameManagement { class cWeaponPickupSpawnPoint; }
namespace Activity { class cCampaignWeaponSpawnPoint; }

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
        // RuffKing's four states, each with its own Begin/End/Process. In CD2 only Process of STATE_Active and
        // STATE_Paused does anything (0x82605950, both: the timer countdown back to idle), so the linker folded
        // Deactivated's and Idle's tables (0x8211EF40) and Active's and Paused's (0x8211EF4C), which the getters
        // 0x826047E8..0x826048D8 install.
        class STATE_Deactivated : public Fun_Runtime::State
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Deactivated, CD2_SIZE(STATE_Deactivated, 8))
        };
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
        class STATE_Paused : public Fun_Runtime::State
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Paused, CD2_SIZE(STATE_Paused, 8))
        };
        static Fun_Runtime::State *StaticRetSTATE_Deactivated();
        static Fun_Runtime::State *StaticRetSTATE_Idle();
        static Fun_Runtime::State *StaticRetSTATE_Active();
        static Fun_Runtime::State *StaticRetSTATE_Paused();
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
        // CD2 script names at 0x826050B0/0x826050C0; reference const signatures.
        unsigned int GetID() const;
        eEquipmentType RetEquipmentType() const;
        virtual int RetUpperAimIndex() const;
        virtual int RetUpperReloadIndex() const;
        virtual int RetUpperFireIndex() const;
        virtual int RetUpperEquipIndex() const;
        virtual bool IsLive();                                  // 330
        virtual bool IsDetonating();
        // Burn's IsStuck, which RuffKing lacks: cCWSatchelCharge's table (0x821234F8) returns its stuck flag here.
        // CD2's weapon tables (cWeapon 0x8211F3C8, cCWWeapon 0x8211FD38, cGrenade 0x82014DD0) hold the false stub at
        // 332, the clip-plus-stored sum (0x82607A80, RetTotalAmmo) at 333 and the stored-ammo test (0x82378A28,
        // HasMaxAmmo) at 334.
        virtual bool IsStuck();                                 // 332
        virtual unsigned int RetTotalAmmo() const;
        virtual bool HasMaxAmmo() const;
        // 335 returns m_bMarkedForDeletion (0x82604748); CanBeEquipped (337, 0x82605CB8) and CanSpawnPickupVFX (346,
        // 0x822DC5D0) call slot 335 first, as RuffKing's call IsMarkedForDeletion; cGrenade's 336 forwards its owner
        // argument to cEquipment's (0x82605C10), RuffKing's PickUpRequested.
        virtual bool IsMarkedForDeletion();                     // 335
        virtual bool PickUpRequested(cGameBase *pOwnerTest);
        virtual bool CanBeEquipped();
        // cCWFirearm's 338..341 (0x82618118..0x826181C8) toggle, activate and deactivate its UV light and return
        // whether it is on, in RuffKing's order.
        virtual void ToggleLightAttachment();
        virtual void ActivateLightAttachment();
        virtual void DeactivateLightAttachment();               // 340
        virtual bool IsLightAttachmentActive() const;
        virtual void NotifyTracked(cEquipment *);
        virtual Fun_Runtime::Mtx *GetMatrix(Fun_Runtime::Mtx &Mat);
        virtual void CreateDynamicObstacle();
        virtual void DestroyDynamicObstacle();                  // 345
        // CD2 has no GetNetDebugString (RuffKing's and Burn's slot after CanSpawnPickupVFX): slot 347 returns
        // m_bNetSleeping as RuffKing's CanForceNetTransform does, and 349 returns true (CanReleaseNetOwnershipOnInitMsg).
        virtual bool CanSpawnPickupVFX();
        // Inline here: CD2 expands it into cCWSatchelCharge::CanForceNetTransform (0x8261CA48), while keeping the
        // out-of-line copy (0x826066A8) for the tables.
        virtual bool CanForceNetTransform() const { return m_bNetSleeping; }
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
            // CD2 inlines these reference accessors into the instance's script getters.
            unsigned int GetID() const { return m_nID; }
            eEquipmentType RetEquipmentType() const { return m_EquipmentType; }

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

            // Reference field follows m_EquipmentType; CD2 GetID (0x826050B0) reads +0x2D0.
            unsigned int m_nID;

        private:
            unsigned char m_unmodelled2D4[0x2F0 - 0x2D4];

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
                CD2_OFFSET(cEquipmentPrototype, m_EquipmentType, 0x2CC)
                CD2_OFFSET(cEquipmentPrototype, m_nID, 0x2D0))
        };

        // CD2 placement factory forwards only this; later reference builds add a prototype argument.
        cEquipment();
        // CD2 0x826046A8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FCB2A0 names placement factory 0x826046b8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // RuffKing's (out of line there); CD2's PickUpRequested (0x82605C10) and CanDoOwnershipTransition (0x82606A98)
        // read the status field directly.
        EQUIP_STATUS GetStatus() const { return m_EquipmentStatus; }
        static const Fun_Runtime::cClass *ms_pcEquipmentClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    protected:
        // Reference member order; CD2 RetPointOfInterest (0x82605008) returns the aligned member at +0x7B0,
        // followed by the status at +0x7E0 (initialized by constructor 0x82604AF8).
        GOM::cPointOfInterest m_POI;
        EQUIP_STATUS m_EquipmentStatus;
        // RuffKing m_fTimer follows equipment status. CD2 constructor 0x82604AF8
        // initializes it at +0x7E4; cWeapon::BeginAttack and both reload completions
        // write this same timer, independently of cWeapon's own attack timer.
        float m_fTimer;
        // RuffKing's fields from here to the end, in its order and 0x20 earlier in CD2 (its class is 0x890 bytes, CD2's
        // 0x870): slot 335 (0x82604748) returns +0x7F0, CanSpawnPickupVFX (0x822DC5D0) tests +0x85D/+0x85E and
        // LeaveRenderableState (0x82605B40) +0x854, as RuffKing's do at 0x810, 0x87D/0x87E and 0x874.
        enum etDeletionType
        {
            eDT_Dropped = 1,
            eDT_Pickup = 2,
        };
        VFX::cParticleEffectInstance *m_pPickupVFX;                         // 0x7E8
        int m_nPickupVFXID;                                                 // 0x7EC
        bool m_bMarkedForDeletion;                                          // 0x7F0
        float m_fDeletionTimer;                                             // 0x7F4
        etDeletionType m_eDeletionType;                                     // 0x7F8
        unsigned int m_nMarkedForDeletionTime;                              // 0x7FC
        float m_fPickupVFXFadeTimer;                                        // 0x800
        float m_bRenderPickUpVFX;                                           // 0x804
        bool m_bAvailableToPlayer;                                          // 0x808
        // Constructor 0x82604AF8 clears +0x809; primary slot 347 (0x826066A8) returns this byte.
        bool m_bNetSleeping;                                                // 0x809
        Fun_Runtime::Mtx m_SleepTransform;                                  // 0x810
        GameManagement::cWeaponPickupSpawnPoint *m_pWeaponSpawnPoint;       // 0x850
        bool m_bMultiplayerPickup;                                          // 0x854
        Activity::cCampaignWeaponSpawnPoint *m_pCampaignWeaponSpawnPoint;   // 0x858
        bool m_bCampaignPickup;                                             // 0x85C
        bool m_bDeliverablePickup;                                          // 0x85D
        bool m_bAttachedToVehicle;                                          // 0x85E
        bool m_bSpawnedPickupVFX;                                           // 0x85F
        bool m_bInfiniteAmmo;                                               // 0x860
        bool m_bDropping;                                                   // 0x861
        // CD2: cEquipment's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x82608200
        virtual void TickUpdate(float fDeltaTime); // 23: 0x822D04B8
        virtual void UpdateRenderMatrix(); // 26: 0x822DD5A0
        virtual void LeaveRenderableState(); // 32: 0x82605B40
        virtual bool IsManagedByActivityManager(); // 62: 0x82605FD0
        virtual void Slot64(); // 63: 0x82605D20
        virtual void vf76(); // 76: 0x822E88B0
        virtual void vf86(); // 86: 0x826057A8
        virtual void vf87(); // 87: 0x826058A8
        virtual void vf91(); // 91: 0x82605710
        virtual void vf92(); // 92: 0x82605610
        virtual GOM::cPointOfInterest *RetPointOfInterest(int nPoint); // 122: 0x82605008
        virtual unsigned char RetNumPointsOfInterest(); // 123: 0x8288FB78, unlike cNetDynamicBody's zero return.
        virtual void vf127(); // 127: 0x82605010
        virtual void CreateHavokPhysics(); // 153: 0x82604F98
        virtual void DeleteHavokPhysics(); // 154: 0x82604FA0
        virtual void vf158(); // 158: 0x82689BF0
        virtual void vf168(); // 168: 0x822CDDC0
        virtual void vf244(); // 244: 0x8288FB78
        virtual void vf245(); // 245: 0x827E56A8
        virtual void vf254(); // 254: 0x822C5A30
        virtual void vf257(); // 257: 0x822312B0
        // virtual void ImpactAudio(float fDeltaVelocity); // 258: 0x82608838
        // virtual void ScrapeAudio(float fRelativeVelocity); // 259: 0x82608850
        // virtual void PickUpAudio(); // 260: 0x82608868
        // virtual void WaterEntryAudio(float); // 261: 0x82608880
        // virtual void WaterExitAudio(float); // 262: 0x826088D8
        // Reconstruction update: cEquipment table 0x82010000 slots 258..262
        // retain cDynamicBody's empty body 0x82580578. These former declarations
        // attributed later derived overrides to the equipment base.
        virtual void vf272(); // 272: 0x827454F8
        virtual void vf280(); // 280: 0x827E56A8
        virtual void vf281(); // 281: 0x8288FB78
        virtual void vf282(); // 282: 0x827E56A8
        // CD2 expands this free-status guard into cGrenade::TriggerEnterWater
        // (0x8261F1A0), while retaining these out-of-line virtual entries.
        virtual void TriggerEnterWater(float fWaterLevel) // 284: 0x82605CF0
        {
            if (m_EquipmentStatus == STATUS_FREE)
                PHYSICS::cNetDynamicBody::TriggerEnterWater(fWaterLevel);
        }
        virtual void TriggerExitWater(float fWaterLevel) // 285: 0x82605D08
        {
            if (m_EquipmentStatus == STATUS_FREE)
                PHYSICS::cNetDynamicBody::TriggerExitWater(fWaterLevel);
        }
        virtual void vf295(); // 295: 0x82580578
        virtual void ReleaseAttachedVFX(bool bReleaseNonCullable); // 296: 0x82580578
        virtual void EndInterpolationOptional(); // 304: 0x82580578
        virtual void SetDeletingReason(char); // 309: 0x82580578
        virtual char GetDeletingReason(); // 310: 0x827E56A8
        // Constructor 0x82604AF8's tables also differ from cNetDynamicBody's at these slots.
        virtual bool EnterPhysicalState(); // 7: 0x82605A38
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x8228C898
        virtual void LeavePhysicalState(); // 27: 0x821D0000
        virtual void vf217(); // 217: 0x82604F40
        virtual void EnterGhostState(); // 271: 0x82605B90
        virtual const Fun_Runtime::cClass &RetClass() const; // cRegisteredClass 0: 0x826045E0
        virtual bool IsA(const Fun_Runtime::cClass &) const; // cRegisteredClass 1: 0x826045F0
        virtual void SetPingedFieldStatesForNode(unsigned char); // cReplicatedClass 20: 0x82606B50
        virtual void SetNetRole(etNetRole); // cNetRoleObject 1: 0x82606B80
        virtual void CalculateRelevancy(int); // cReplicatedClass 2: 0x825DEEE0
        virtual void CalculateLOD(int); // cReplicatedClass 3: 0x826066B0
        virtual bool CanSendTermPacketOnNotRelevant() const; // cReplicatedClass 4: 0x8288FB78
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x82606198
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x822F3468
        virtual void ReplicateHeaderData(); // cReplicatedClass 10: 0x82605FE0
        // Constructor 0x82604AF8's replication table (0x8211EE70) overrides the two slots cNetDynamicBody leaves pure.
        virtual bool IsSequential() const; // cReplicatedClass 6: 0x827E56A8
        virtual bool IsOwnedLocally(); // cReplicatedClass 14: 0x82537F88
        virtual unsigned int GetNumObjectIDBits() const; // cReplicatedClass 16: 0x8288E558
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const; // cReplicatedClass 22: 0x8288CA00
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x8288E110
    protected:
        virtual void EventTriggerStartFire(CHARACTER::cCharacter *); // cIgnitable 10: 0x82580578
        virtual void EventTriggerEndFire(); // cIgnitable 12: 0x82580578
    private:
        CD2_LAYOUT_CHECKS(cEquipment,
            CD2_SIZE(cEquipment, 0x870)
            CD2_OFFSET(cEquipment, m_POI, 0x7B0)
            CD2_OFFSET(cEquipment, m_EquipmentStatus, 0x7E0)
            CD2_OFFSET(cEquipment, m_fTimer, 0x7E4)
            CD2_OFFSET(cEquipment, m_bMarkedForDeletion, 0x7F0)
            CD2_OFFSET(cEquipment, m_bNetSleeping, 0x809)
            CD2_OFFSET(cEquipment, m_SleepTransform, 0x810)
            CD2_OFFSET(cEquipment, m_bMultiplayerPickup, 0x854)
            CD2_OFFSET(cEquipment, m_bDeliverablePickup, 0x85D)
            CD2_OFFSET(cEquipment, m_bDropping, 0x861))
    };
}

#endif // EQUIP_CEQUIPMENT_H
