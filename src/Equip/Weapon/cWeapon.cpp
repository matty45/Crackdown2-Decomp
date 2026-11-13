// Script registrar source ownership: CD2 initializer 0x82FCBE80 names cWeapon,
// and cleanup 0x8303F398 destroys the same descriptor. Shared interface names are ours.
// cWeaponProjectile shares this original object (RuffKing cWeapon.obj and cWeapon.h).
// CD2's cWeaponPrototype::Init reads this object's Ret_OK at 0x83838A28, confirming
// that the former class-only projectile split must be consolidated with this source.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Equip/cWeapon.h"
#include "Equip/cWeaponProjectile.h"
#include "Equip/cGrenade.h"
#include "fun_runtime/script_type_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"
#include "cd2/memory.h"
#include "rw/rwmem.h"
#include "fun_runtime/const_script_method.h"
#include "fun_runtime/pointer_list_impl.h"

namespace Equip
{
    bool cWeapon::IsEmpty() const
    {
        return NeedsReload() && m_nCurrentClipAmmo == 0
            && static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nMaxClipAmmo != 0;
    }

    bool cWeapon::CanAttack()
    {
        if (RetOwner() != NULL && RetOwner()->RetNetRole() == eNR_Authority)
        {
            if (!IsIdle())
                return false;
            if (IsEmpty())
                return false;
        }
        return true;
    }

    void cWeapon::STATE_Reloading::EndState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->EndReloading();
    }

    bool cWeapon::FinishReload()
    {
        m_fTimer = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        GoTo_State(RetSTATE_Idle());
        return true;
    }

    const Fun_Runtime::cClass &cWeapon::RetClass() const
    {
        return *ms_pcWeaponClass;
    }

    const char *cWeapon::RetClassName() const
    {
        return "cWeapon";
    }

    unsigned int cWeapon::IncrementClipAmmo(unsigned int amount)
    {
        const unsigned int maximum = static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nMaxClipAmmo;
        const unsigned int added = m_nCurrentClipAmmo + amount > maximum
            ? maximum - m_nCurrentClipAmmo : amount;
        m_nCurrentClipAmmo += added;
        return added;
    }

    unsigned int cWeapon::DecrementClipAmmo(unsigned int amount)
    {
        const unsigned int removed = amount > m_nCurrentClipAmmo ? m_nCurrentClipAmmo : amount;
        m_nCurrentClipAmmo -= removed;
        return removed;
    }

    void cWeapon::BeginReloading()
    {
        // CD2 and RuffKing both make this virtual query, discard its returned
        // duration, and then start a fixed three-second reload timeout.
        RetReloadDuration();
        m_bReloading = true;
        m_fTimer = 3.0f;
    }

    void cWeapon::SetCurrentAmmoCount(unsigned int ammo)
    {
        m_nCurrentClipAmmo = ammo;
    }

    inline Fun_Runtime::State *cWeapon::StaticRetSTATE_Reloading()
    {
        static STATE_Reloading s_State;
        return &s_State;
    }

    Fun_Runtime::State *cWeapon::RetSTATE_Reloading()
    {
        return StaticRetSTATE_Reloading();
    }

    Fun_Runtime::State *cWeapon::RetSTATE_Reloading() const
    {
        return StaticRetSTATE_Reloading();
    }

    unsigned int cWeapon::IncrementStoredAmmo(unsigned int amount)
    {
        unsigned int added = 0;
        if (!IsUsingInfiniteAmmo())
        {
            const unsigned int maximum = static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nMaxStoredAmmo;
            added = m_nCurrentStoredAmmo + amount > maximum ? maximum - m_nCurrentStoredAmmo : amount;
            m_nCurrentStoredAmmo += added;
        }
        return added;
    }

    void cWeapon::NotifyReloadComplete()
    {
        m_fTimer = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
        GoTo_State(RetSTATE_Idle());
    }

    bool cWeapon::NeedsReload() const
    {
        return m_nCurrentClipAmmo < static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nMaxClipAmmo
            && !IsInfiniteClip();
    }

    Fun_Runtime::cClass &cWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x80, "cWeapon", 0x8C0);
        return *descriptor;
    }

    cWeapon::~cWeapon()
    {
    }

    unsigned int cWeapon::DecrementStoredAmmo(unsigned int amount)
    {
        if (IsUsingInfiniteAmmo())
            return amount;
        const unsigned int removed = amount > m_nCurrentStoredAmmo ? m_nCurrentStoredAmmo : amount;
        m_nCurrentStoredAmmo -= removed;
        return removed;
    }

    void cWeapon::EndReloading()
    {
        m_bReloading = false;
    }

    void cWeapon::STATE_Reloading::BeginState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->BeginReloading();
    }

    RWS::CAttributeHandler *cWeapon::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeaponPrototype(packet);
    }

    RWS::CAttributeHandler *cWeapon::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cWeapon;
        return 0;
    }

    float cWeapon::RetAttackDuration() const
    {
        return Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
    }

    const Fun_Runtime::cClass &cWeaponProjectile::RetClass() const
    {
        return *ms_pcWeaponProjectileClass;
    }

    RWS::CAttributeHandler *cWeaponProjectile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cWeaponProjectilePrototype(packet);
    }

    const char *cWeaponProjectile::RetClassName() const
    {
        return "cWeaponProjectile";
    }

    RWS::CAttributeHandler *cWeaponProjectile::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cWeaponProjectile;
        return 0;
    }

    // CD2 0x82609610 and 0x826096C0: no derived construction or cleanup beyond the vtables.
    cWeaponProjectile::cWeaponProjectile()
    {
    }

    cWeaponProjectile::~cWeaponProjectile()
    {
    }

    inline Fun_Runtime::State *cWeapon::StaticRetSTATE_Idle()
    {
        static STATE_Idle s_State;
        return &s_State;
    }

    Fun_Runtime::State *cWeapon::RetSTATE_Idle()
    {
        return StaticRetSTATE_Idle();
    }

    Fun_Runtime::State *cWeapon::RetSTATE_Idle() const
    {
        return StaticRetSTATE_Idle();
    }

    inline Fun_Runtime::State *cWeapon::StaticRetSTATE_Active()
    {
        static STATE_Active s_State;
        return &s_State;
    }

    Fun_Runtime::State *cWeapon::RetSTATE_Active()
    {
        return StaticRetSTATE_Active();
    }

    Fun_Runtime::State *cWeapon::RetSTATE_Active() const
    {
        return StaticRetSTATE_Active();
    }

}

// The explicit registrar specialization must be defined in its template's
// namespace, between the surrounding weapon definitions in CD2 address order.
namespace Fun_Runtime
{
    template <>
    void cScriptTypeRegistrar<Equip::cWeapon>::RegisterMethods()
    {
        RegisterMethod(&Equip::cWeapon::RetCurrentAmmoCount, "RetCurrentAmmoCount");
        RegisterMethod(&Equip::cWeapon::RetMaxAmmoCount, "RetMaxAmmoCount");
        RegisterMethod(&Equip::cWeapon::CanReload, "CanReload");
        RegisterMethod(&Equip::cWeapon::NeedsReload, "NeedsReload");
        RegisterMethod(&Equip::cWeapon::IsEmpty, "IsEmpty");
        RegisterMethod(&Equip::cWeapon::IsAmmoLow, "IsAmmoLow");
        RegisterMethod(&Equip::cWeapon::RetLowAmmoThreshold, "RetLowAmmoThreshold");
        RegisterMethod(&Equip::cWeapon::RetMaxOptimalRange, "RetMaxOptimalRange");
        RegisterMethod(&Equip::cWeapon::RetMinOptimalRange, "RetMinOptimalRange");
    }
}

namespace Equip
{
    bool cWeapon::Activate()
    {
        return InitiateAttack();
    }

    bool cWeapon::Deactivate()
    {
        GoTo_State(RetSTATE_Idle());
        return true;
    }

    bool cWeapon::InitiateReload()
    {
        bool entered = false;
        if (HasStoredAmmo())
            entered = GoTo_State(RetSTATE_Reloading());
        return entered;
    }

    bool cWeapon::CanReload() const
    {
        return !IsTurretWeapon() && HasStoredAmmo() && NeedsReload();
    }

    // CD2 keeps this cWeapon body beside the projectile code. The script registrar
    // names RetMaxAmmoCount, and its prototype field belongs to cWeaponPrototype.
    unsigned int cWeapon::RetMaxAmmoCount() const
    {
        return static_cast<const cWeaponPrototype *>(m_pPrototype)->RetMaxClipAmmo();
    }

    float cWeapon::RetLowAmmoThreshold() const
    {
        return static_cast<float>(static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nMaxClipAmmo) * 0.4f;
    }

    void cWeapon::SetCurrentStoredAmmo(unsigned int ammo)
    {
        const unsigned int maximum = static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nMaxStoredAmmo;
        if (ammo > maximum)
            m_nCurrentStoredAmmo = maximum;
        else
            m_nCurrentStoredAmmo = ammo;
    }

    bool cWeapon::HasStoredAmmo() const
    {
        if (IsUsingInfiniteAmmo())
            return true;
        return m_nCurrentStoredAmmo != 0;
    }

    unsigned int cWeapon::RetWeaponPriority() const
    {
        return static_cast<const cWeaponPrototype *>(m_pPrototype)->m_nWeaponPriority;
    }

    float cWeapon::RetMaxOptimalRange() const
    {
        return static_cast<const cWeaponPrototype *>(m_pPrototype)->m_fMaxOptimalRange;
    }

    float cWeapon::RetMinOptimalRange() const
    {
        return static_cast<const cWeaponPrototype *>(m_pPrototype)->m_fMinOptimalRange;
    }

    void cWeapon::STATE_Reloading::Process(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->ProcessReloading();
    }

    void cWeapon::STATE_Active::BeginState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->BeginAttack();
    }

    void cWeapon::STATE_Active::Process(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->ProcessAttack();
    }

    void cWeapon::STATE_Active::EndState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->EndAttack();
    }

    bool cWeapon::BeginAttack()
    {
        m_fTimer = RetAttackDuration();
        cGameBase *owner = RetOwnerGameObject();
        if (owner)
            owner->GetAimMatrix(m_matActivateMatrix);
        return true;
    }

    void cWeapon::STATE_Idle::BeginState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->BeginIdle();
    }

    void cWeapon::STATE_Idle::Process(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->ProcessIdle();
    }

    void cWeapon::STATE_Idle::EndState(Fun_Runtime::cStateMachine *machine)
    {
        static_cast<cWeapon *>(machine)->EndIdle();
    }

    cWeapon::cWeaponPrototype::cWeaponPrototype(const RWS::CAttributePacket &packet)
        : cEquipment::cEquipmentPrototype(packet),
          m_vecStandingMuzzlePosition(Fun_Runtime::ZeroVec),
          m_vecCrouchingMuzzlePosition(Fun_Runtime::ZeroVec),
          m_vecLeaningOverWallMuzzlePosition(Fun_Runtime::ZeroVec),
          m_nMaxClipAmmo(0), m_nMaxStoredAmmo(0), m_nInitialAmmoCount(0),
          m_MinAIRandomAmmo(0), m_MaxAIRandomAmmo(0),
          m_fMaxOptimalRange(0.0f), m_fMinOptimalRange(0.0f),
          m_nWeaponPriority(0), m_nPvPKillPoints(0), m_bUV(false)
    {
        m_EquipmentCategory = CATEGORY_WEAPON;
        m_EquipmentType = eEquipT_Primary;
    }

    void cWeapon::cWeaponPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cEquipment::cEquipmentPrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cWeapon"); !it.IsFinished(); ++it)
        {
            // CD2 groups ammo updates before the muzzle-vector cases.
            switch (it->GetCommandId())
            {
            case CMD_Priority:
                m_nWeaponPriority = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_Max_Optimal_Range:
            {
                float range = it->GetAs_float();
                RwMemNative32(&range, sizeof(range));
                m_fMaxOptimalRange = range;
                break;
            }
            case CMD_Min_Optimal_Range:
            {
                float range = it->GetAs_float();
                RwMemNative32(&range, sizeof(range));
                m_fMinOptimalRange = range;
                break;
            }
            case CMD_MaxAmmoCount:
                m_nMaxClipAmmo = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_MaxStoredAmmo:
                m_nMaxStoredAmmo = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_InitialAmmoCount:
                m_nInitialAmmoCount = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_MinAIRandomAmmo:
                m_MinAIRandomAmmo = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_MaxAIRandomAmmo:
                m_MaxAIRandomAmmo = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_MUZZLE_POSITION_STANDING:
                m_vecStandingMuzzlePosition = it->GetAs_Vec3();
                break;
            case CMD_MUZZLE_POSITION_CROUCHING:
                m_vecCrouchingMuzzlePosition = it->GetAs_Vec3();
                break;
            case CMD_MUZZLE_POSITION_LEANING_OVER_WALL:
                m_vecLeaningOverWallMuzzlePosition = it->GetAs_Vec3();
                break;
            case CMD_PVP_KILL_POINTS:
                m_nPvPKillPoints = rwSwap32(it->GetAs_UInt32());
                break;
            case CMD_UV:
                m_bUV = rwSwap32(it->GetAs_UInt32()) != 0;
                break;
            }
        }
    }

    Fun_Runtime::RetVal cWeapon::cWeaponPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    Fun_Runtime::cClass &cWeaponProjectile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cWeaponProjectileClass = new Fun_Runtime::cClass(0x26EE0, "cWeaponProjectile", 0x870);
        return *cWeaponProjectileClass;
    }

    const Fun_Runtime::cClass *cWeapon::ms_pcWeaponClass = &cWeapon::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cWeaponcEquipmentInheritRegistrar(
        cWeapon::StaticCreateClass(), cEquipment::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cWeaponRegistrar(
        "cWeapon", cWeapon::MakeNew, 0x8C0, false);

    static GOM::cProtoRegistrar cWeaponSpawningRegistrar(
        cWeapon::StaticCreateClass(), cWeapon::SpawnFromPrototype);

    static Fun_Runtime::cScriptTypeRegistrar<cWeapon> cWeaponScriptRegistrar(
        "cWeapon", "cEquipment");

    const Fun_Runtime::cScriptTypeRegistration *cWeapon::RetScriptTypeRegistration() const
    {
        return &cWeaponScriptRegistrar;
    }

    const Fun_Runtime::cClass *cWeaponProjectile::ms_pcWeaponProjectileClass = &cWeaponProjectile::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cWeaponProjectilecEquipmentInheritRegistrar(
        cWeaponProjectile::StaticCreateClass(), cEquipment::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cWeaponProjectileRegistrar(
        "cWeaponProjectile", cWeaponProjectile::MakeNew, 0x870, false);

    // CD2 0x82FCBFB8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cWeaponProjectileSpawningRegistrar(
        cWeaponProjectile::StaticCreateClass(), cWeaponProjectile::SpawnFromPrototype);

    // cGrenade's inline getters (RuffKing cGrenade.h): CD2 keeps their one copy in this object's text, after its
    // adjustor thunks (0x8260AAA8, 0x8260AAB0).
    bool cGrenade::HasDetonated()
    {
        return m_bDetonated;
    }

    bool cGrenade::IsLive()
    {
        return m_bLive;
    }
}
