// STAND-IN: RuffKing names cEquipment as the base; CD2 constructor 0x82609AA8
// confirms that constructor chain. Descriptor 0x822E5B60 gives complete size 0x8C0.
// Instance data beyond the recovered base is opaque; no field offsets are inferred from it.
// Reconstruction update: CD2's constructor now establishes the complete own field block below.
#ifndef EQUIP_CWEAPON_H
#define EQUIP_CWEAPON_H
#include "Equip/cEquipment.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/mtx.h"
#include "CHARACTER/cCharacter.h"
#include "RPG/eSkills.h"
namespace Equip
{
    class cWeapon : public cEquipment
    {
    public:
        // CD2 weapon interface extends the 363-slot equipment interface; reference virtual order gives 43 own slots. Names/signatures of these slots remain unrecovered.
        virtual void vf363(); // primary slot 363
        virtual void vf364(); // primary slot 364
        virtual bool Deactivate(); // primary slot 365
        virtual void vf366(); // primary slot 366
        virtual void InitMaxAmmo(); // primary slot 367
        virtual bool HasStoredAmmo() const; // primary slot 368
        virtual bool IsUsingInfiniteAmmo() const; // primary slot 369
        virtual void vf370(); // primary slot 370
        virtual void SetCurrentAmmoCount(unsigned int); // primary slot 371
        virtual void SetCurrentStoredAmmo(unsigned int); // primary slot 372
        virtual void SetInfiniteClip(bool); // primary slot 373
        virtual bool IsInfiniteClip() const; // primary slot 374
        virtual void BeginIdle(); // primary slot 375
        virtual void ProcessIdle(); // primary slot 376
        virtual void EndIdle(); // primary slot 377
        // Reference IsIdle query; CD2 CanAttack compares this state's singleton.
        bool IsIdle() { return IsIn_State(RetSTATE_Idle()); }
    protected:
        virtual bool BeginAttack(); // primary slot 378
        virtual void ProcessAttack(); // primary slot 379
        virtual void EndAttack(); // primary slot 380
    public:
        virtual bool CanAttack(); // primary slot 381
        virtual bool InitiateAttack(); // primary slot 382
        virtual float RetAttackDuration() const; // primary slot 383
    protected:
        virtual Fun_Runtime::State *RetSTATE_Reloading(); // primary slots 384/385 (overloads reverse)
        virtual Fun_Runtime::State *RetSTATE_Reloading() const;
        virtual void BeginReloading(); // primary slot 386
        virtual void ProcessReloading(); // primary slot 387
        virtual void EndReloading(); // primary slot 388
    public:
        virtual void NotifyReloadComplete(); // primary slot 389
        virtual bool InitiateReload(); // primary slot 390
        virtual bool FinishReload(); // primary slot 391
        virtual bool CanReload() const; // primary slot 392
        virtual bool NeedsReload() const; // primary slot 393
        virtual bool IsEmpty() const; // primary slot 394
        virtual bool IsAmmoLow() const; // primary slot 395
        virtual float RetLowAmmoThreshold() const; // primary slot 396
        virtual unsigned int IncrementStoredAmmo(unsigned int); // primary slot 397
        virtual unsigned int DecrementStoredAmmo(unsigned int); // primary slot 398
        virtual unsigned int IncrementClipAmmo(unsigned int); // primary slot 399
        virtual unsigned int DecrementClipAmmo(unsigned int); // primary slot 400
        virtual float RetReloadDuration() const; // primary slot 401
        virtual float RetMaxOptimalRange() const; // primary slot 402
        virtual float RetMinOptimalRange() const; // primary slot 403
        virtual void vf404(); // primary slot 404
        virtual void vf405(); // primary slot 405

        // Reference direct State base; CD2 table 0x8211FBA8 has exactly three slots.
        class STATE_Reloading : public Fun_Runtime::State
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Reloading, CD2_SIZE(STATE_Reloading, 8))
        };

    protected:
        // RuffKing's shared state base; CD2 0x82609820 installs the table
        // 0x8211FB90 with Begin/End/Process at 0x8260A238/0x8260A278/0x8260A258.
        class STATE_Idle : public cEquipment::STATE_Idle
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Idle, CD2_SIZE(STATE_Idle, 8))
        };
        // CD2 getter 0x82609870 installs 0x8211FB9C: Begin/End/Process
        // are 0x8260A040/0x8260A080/0x8260A060. Shared base and names are RuffKing's.
        class STATE_Active : public cEquipment::STATE_Active
        {
        public:
            virtual void BeginState(Fun_Runtime::cStateMachine *);
            virtual void EndState(Fun_Runtime::cStateMachine *);
            virtual void Process(Fun_Runtime::cStateMachine *);
            CD2_LAYOUT_CHECKS(STATE_Active, CD2_SIZE(STATE_Active, 8))
        };
        static Fun_Runtime::State *StaticRetSTATE_Idle();
        static Fun_Runtime::State *StaticRetSTATE_Active();
        static Fun_Runtime::State *StaticRetSTATE_Reloading();
        virtual Fun_Runtime::State *RetSTATE_Idle();
        virtual Fun_Runtime::State *RetSTATE_Idle() const;
        virtual Fun_Runtime::State *RetSTATE_Active();
        virtual Fun_Runtime::State *RetSTATE_Active() const;

    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // Reference attribute IDs; CD2's switch at 0x8260A460 uses the same 0..12 sequence.
        enum LoadParameterTypes
        {
            CMD_Priority = 0, CMD_Max_Optimal_Range, CMD_Min_Optimal_Range,
            CMD_MUZZLE_POSITION_STANDING, CMD_MUZZLE_POSITION_CROUCHING,
            CMD_MUZZLE_POSITION_LEANING_OVER_WALL, CMD_InitialAmmoCount,
            CMD_MaxAmmoCount, CMD_MaxStoredAmmo, CMD_MinAIRandomAmmo,
            CMD_MaxAIRandomAmmo, CMD_PVP_KILL_POINTS, CMD_UV
        };
        // Interface-only prototype stand-in: name and base from RuffKing.
        // Instance fields and complete size are not recovered; this is not an allocation layout.
        // Reconstruction update: the own prototype fields are now established by CD2's constructor and getters.
        // Name and base from RuffKing. CD2's constructor (0x8260A370) calls cEquipmentPrototype's and initializes
        // 0x29C..0x34B; cGrenadePrototype's constructor (0x8261F758) starts its own fields at 0x350.
        class cWeaponPrototype : public cEquipment::cEquipmentPrototype
        {
            friend class cWeapon;
        public:
            cWeaponPrototype(const RWS::CAttributePacket &);
            // CD2's shared deleting wrapper (0x82623BE0) restores both of these
            // prototype vptrs before calling cEquipmentPrototype's destructor.
            virtual ~cWeaponPrototype() {}
            // CD2 prototype table 0x8211FB20 has this own Init at slot 5 (0x8260A790).
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
            // CD2 table 0x8211FB20 differs from cEquipmentPrototype at these slots too.
            virtual void HandleAttributes(const RWS::CAttributePacket &);
            virtual unsigned int RetPvPKillPoints() const;

            // Reference-named accessor; CD2 RetMaxAmmoCount reads this field at +0x320.
            unsigned int RetMaxClipAmmo() const { return m_nMaxClipAmmo; }

        protected:
            // CD2 constructor 0x8260A370 initializes three muzzle vectors followed by
            // the reference ammo/range fields. Later builds omit the third vector;
            // the CMD_MUZZLE_POSITION_LEANING_OVER_WALL command supplies its name here.
            Fun_Runtime::Vec3 m_vecStandingMuzzlePosition;
            Fun_Runtime::Vec3 m_vecCrouchingMuzzlePosition;
            Fun_Runtime::Vec3 m_vecLeaningOverWallMuzzlePosition;
            unsigned int m_nMaxClipAmmo;
            unsigned int m_nMaxStoredAmmo;
            unsigned int m_nInitialAmmoCount;
            unsigned int m_MinAIRandomAmmo;
            unsigned int m_MaxAIRandomAmmo;
            float m_fMaxOptimalRange;
            float m_fMinOptimalRange;
            unsigned int m_nWeaponPriority;
            unsigned int m_nSecondaryTextureRow;
            unsigned int m_nPvPKillPoints;
            bool m_bUV;

        private:
            CD2_LAYOUT_CHECKS(cWeaponPrototype,
                CD2_SIZE(cWeaponPrototype, 0x350)
                CD2_OFFSET(cWeaponPrototype, m_vecStandingMuzzlePosition, 0x2F0)
                CD2_OFFSET(cWeaponPrototype, m_vecCrouchingMuzzlePosition, 0x300)
                CD2_OFFSET(cWeaponPrototype, m_vecLeaningOverWallMuzzlePosition, 0x310)
                CD2_OFFSET(cWeaponPrototype, m_nMaxClipAmmo, 0x320)
                CD2_OFFSET(cWeaponPrototype, m_nMaxStoredAmmo, 0x324)
                CD2_OFFSET(cWeaponPrototype, m_nInitialAmmoCount, 0x328)
                CD2_OFFSET(cWeaponPrototype, m_MinAIRandomAmmo, 0x32C)
                CD2_OFFSET(cWeaponPrototype, m_MaxAIRandomAmmo, 0x330)
                CD2_OFFSET(cWeaponPrototype, m_fMaxOptimalRange, 0x334)
                CD2_OFFSET(cWeaponPrototype, m_fMinOptimalRange, 0x338)
                CD2_OFFSET(cWeaponPrototype, m_nWeaponPriority, 0x33C)
                CD2_OFFSET(cWeaponPrototype, m_nSecondaryTextureRow, 0x340)
                CD2_OFFSET(cWeaponPrototype, m_nPvPKillPoints, 0x344)
                CD2_OFFSET(cWeaponPrototype, m_bUV, 0x348))
        };

        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcWeaponClass;
        // CD2 0x82609AA8 takes only this; the later reference adds a prototype argument.
        cWeapon();
        virtual ~cWeapon();
        // CD2 primary table 0x8211F3C8 slot 11 overrides cEquipment's name getter.
        virtual const char *RetClassName() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2's script-host table 0x8211FA38 slot 1 returns this class's registrar.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        unsigned int RetMaxAmmoCount() const;
        unsigned int RetCurrentAmmoCount() const { return m_nCurrentClipAmmo; }
        // Reference overloads. CD2 cCWWeapon::RetReloadDuration inlines the owner
        // class test and firearm-skill query, defaulting to level one.
        unsigned char RetFirearmSkillLevel(const cNonGameBase *owner) const
        {
            if (owner && owner->IsA(*CHARACTER::cCharacter::ms_pcCharacterClass))
                return static_cast<const CHARACTER::cCharacter *>(owner)->RetSkill(RPG::eSk_FireArms);
            return 1;
        }
        unsigned char RetFirearmSkillLevel() const { return RetFirearmSkillLevel(RetOwner()); }
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
    protected:
        // Reference member order; CD2 constructor 0x82609AA8 initializes the matrix
        // at +0x870, ammo at +0x8B0/+0x8B4, attack timer at +0x8B8 and two flags.
        Fun_Runtime::Mtx m_matActivateMatrix;
        unsigned int m_nCurrentClipAmmo;
        unsigned int m_nCurrentStoredAmmo;
        float m_fAttackTimer;
        bool m_bReloading;
    private:
        bool m_bInfiniteClip;
        // CD2: cWeapon's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        // virtual void vf140(); // 140: 0x8234A320
        // Reconstruction update: cWeapon's primary table 0x8211F3C8 slot 140
        // retains the base empty body 0x82580578; 0x8234A320 is a later derived override.
        virtual void vf274(); // 274: 0x82335618
        virtual void vf275(); // 275: 0x82609F30
        virtual void vf276(); // 276: 0x82609FA8
    private:
        CD2_LAYOUT_CHECKS(cWeapon,
            CD2_SIZE(cWeapon, 0x8C0)
            CD2_OFFSET(cWeapon, m_matActivateMatrix, 0x870)
            CD2_OFFSET(cWeapon, m_nCurrentClipAmmo, 0x8B0)
            CD2_OFFSET(cWeapon, m_nCurrentStoredAmmo, 0x8B4)
            CD2_OFFSET(cWeapon, m_fAttackTimer, 0x8B8)
            CD2_OFFSET(cWeapon, m_bReloading, 0x8BC)
            CD2_OFFSET(cWeapon, m_bInfiniteClip, 0x8BD))

    public:
        // CD2 table 0x8211F3C8 differs from cEquipment at these inherited slots.
        virtual void Slot13(); // slot 13: 0x823A7408
        virtual void Slot23(); // slot 23: 0x82609BA8
        virtual void vf288(); // slot 288: 0x827E56A8
        virtual void SetStatus(EQUIP_STATUS); // slot 316: 0x82609BF0
        virtual bool Activate(); // slot 318: 0x82609C58
        virtual unsigned int RetWeaponPriority() const; // slot 320: 0x82609F00
        virtual bool HasMaxAmmo() const; // slot 333: 0x82607A80
        virtual bool IsMarkedForDeletion(); // slot 334: 0x82378A28
    };
}
#endif
