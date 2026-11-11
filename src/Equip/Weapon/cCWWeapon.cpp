// src/Equip/Weapon/cCWWeapon.cpp
//
// Class: cCWWeapon (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cCWWeapon.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cCWWeapon.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cCWWeapon.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Equip/cWeapon.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cCWWeapon.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace Equip
{
    void cCWWeapon::NotifyAttackComplete()
    {
        GoTo_State(RetSTATE_Idle());
    }

    void cCWWeapon::InitMaxAmmo()
    {
        SetCurrentAmmoCount(static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nMaxClipAmmo);
        SetCurrentStoredAmmo(static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nMaxStoredAmmo);
    }

    float cCWWeapon::RetAIAccuracyCone() const { return m_fAIAccuracyCone; }
    float cCWWeapon::RetAIInitialAccuracyCone() const { return m_fAIInitialAccuracyCone; }
    float cCWWeapon::RetAIPathClearCone() const { return m_fAIPathClearCone; }
    unsigned int cCWWeapon::RetAINumberOfShotsToFullAccuracy() const
    {
        return m_uiAINumberOfShotsToReachFullAccuracy;
    }
    unsigned int cCWWeapon::RetNumberOfShotsTaken() const { return m_uiShotCount; }

    Prop::cTurretBase *cCWWeapon::RetTurretMounted() const
    {
        return m_pTurret;
    }

    bool cCWWeapon::IsTurretWeapon() const
    {
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->IsTurretWeapon();
    }

    const Fun_Runtime::cClass *cCWWeapon::ms_pcCWWeaponClass = &cCWWeapon::StaticCreateClass();

    Fun_Runtime::cClass &cCWWeapon::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cCWWeaponClass = new Fun_Runtime::cClass(0x3E82, "cCWWeapon", 0xA10);
        return *cCWWeaponClass;
    }

    static RWS::CClassFactory::CRegistrar cCWWeaponRegistrar(
        "cCWWeapon", cCWWeapon::MakeNew, 0xA10, false);

    // CD2 0x82FCB890: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cCWWeaponSpawningRegistrar(
        cCWWeapon::StaticCreateClass(), cCWWeapon::SpawnFromPrototype);

    // CD2 0x82FCB7D8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cCWWeaponcWeaponInheritRegistrar(
        Equip::cCWWeapon::StaticCreateClass(), Equip::cWeapon::StaticCreateClass());

    RWS::CAttributeHandler *cCWWeapon::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cCWWeaponPrototype(packet);
    }

    const char *cCWWeapon::RetClassName() const
    {
        return "cCWWeapon";
    }

    RWS::CAttributeHandler *cCWWeapon::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cCWWeapon;
        return 0;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cCWWeapon> cCWWeaponScriptRegistrar(
        "cCWWeapon", "cWeapon");

    const Fun_Runtime::cScriptTypeRegistration *cCWWeapon::RetScriptTypeRegistration() const
    {
        return &cCWWeaponScriptRegistrar;
    }

    bool cCWWeapon::CanAttack()
    {
        if (cWeapon::CanAttack())
        {
            if (!RetPintleMount() || m_fAttackTimer > RetAttackDuration())
                return true;
        }
        return false;
    }

    void cCWWeapon::PostAnimUpdate(float)
    {
        UpdateAttachedMuzzleEffect();
    }

    int cCWWeapon::RetNumHands() const
    {
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nNumHands;
    }

    float cCWWeapon::RetReloadDuration() const
    {
        const unsigned char level = RetFirearmSkillLevel();
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_fReloadTime[level - 1];
    }

    void cCWWeapon::SetAIAccuracyCone(float value)
    {
        m_fAIAccuracyCone = value;
    }

    void cCWWeapon::SetAIInitialAccuracyCone(float value)
    {
        m_fAIInitialAccuracyCone = value;
    }

    void cCWWeapon::SetAIPathClearCone(float value)
    {
        m_fAIPathClearCone = value;
    }

    void cCWWeapon::SetAINumberOfShotsToFullAccuracy(unsigned int value)
    {
        m_uiAINumberOfShotsToReachFullAccuracy = value;
    }

    void cCWWeapon::RevertAIAccuracyCone()
    {
        m_fAIAccuracyCone = static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_fAIAccuracyCone;
    }

    void cCWWeapon::ResetNumberOfShotsTaken()
    {
        m_uiShotCount = 0;
    }

    int cCWWeapon::RetUpperAimIndex() const
    {
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nUpperAimIndex;
    }

    int cCWWeapon::RetUpperReloadIndex() const
    {
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nUpperReloadIndex;
    }

    int cCWWeapon::RetUpperFireIndex() const
    {
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nUpperFireIndex;
    }

    int cCWWeapon::RetUpperEquipIndex() const
    {
        return static_cast<const cCWWeaponPrototype *>(m_pPrototype)->m_nUpperEquipIndex;
    }

    cCWWeapon::cCWWeaponPrototype::~cCWWeaponPrototype()
    {
    }

    Fun_Runtime::RetVal cCWWeapon::cCWWeaponPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    Fun_Runtime::cRandGen cCWWeapon::ms_Randomiser;
}
