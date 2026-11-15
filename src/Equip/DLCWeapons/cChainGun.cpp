// src/Equip/DLCWeapons/cChainGun.cpp
//
// Class: cChainGun (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cChainGun.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/DLCWeapons/cChainGun.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/DLCWeapons/cChainGun.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWFirearm.h"
#include "rws/classfactory.h"
#include "Equip/cChainGun.h"
#include "cd2/memory.h"
#include "CHARACTER/cCharacter.h"
#include "RPG/eSkills.h"
#include "fun_runtime/oldvec3.h"
#include <new>

namespace Equip
{
    const Fun_Runtime::cClass &cChainGun::RetClass() const
    {
        return *ms_pcChainGunClass;
    }

    bool cChainGun::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcChainGunClass->IsA(c);
    }

    const Fun_Runtime::cClass *cChainGun::ms_pcChainGunClass = &cChainGun::StaticCreateClass();

    RWS::CAttributeHandler *cChainGun::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cChainGun;
        return 0;
    }

    Fun_Runtime::cClass &cChainGun::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cChainGunClass = new Fun_Runtime::cClass(0x13266, "cChainGun", 0xAC0);
        return *cChainGunClass;
    }

    static RWS::CClassFactory::CRegistrar cChainGunRegistrar(
        "cChainGun", cChainGun::MakeNew, 0xAC0, false);

    // CD2 0x82FCE550: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cChainGuncCWFirearmInheritRegistrar(
        Equip::cChainGun::StaticCreateClass(), Equip::cCWFirearm::StaticCreateClass());

    // CD2 0x82FCE608: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cChainGunSpawningRegistrar(
        cChainGun::StaticCreateClass(), cChainGun::SpawnFromPrototype);

    RWS::CAttributeHandler *cChainGun::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cChainGunPrototype(packet);
    }

    const char *cChainGun::RetClassName() const
    {
        return "cChainGun";
    }

    // CD2 0x82616780 has no derived cleanup beyond vtable restoration.
    cChainGun::~cChainGun()
    {
    }

    void cChainGun::TickUpdate(float fDeltaTime)
    {
        cCWFirearm::TickUpdate(fDeltaTime);
        Animate(fDeltaTime);
    }

    const cChainGun::tChainGunLevelData *cChainGun::RetLevelData() const
    {
        char nLevel = 0;
        const CHARACTER::cCharacter *pOwner = RetOwnerCharacter();
        if (pOwner)
            nLevel = pOwner->RetSkill(RPG::eSk_FireArms) - 1;
        return &RetChainGunPrototype()->m_aChainGunLevelData[nLevel];
    }

    float cChainGun::RetAttackDuration() const
    {
        const tChainGunLevelData *pLevelData = RetLevelData();
        return pLevelData->m_fMaxDuration + (pLevelData->m_fMinDuration - pLevelData->m_fMaxDuration) *
            RetChainGunPrototype()->m_fMaxAngVelRecip * m_fBarrelSpeed;
    }

    cChainGun::cChainGunPrototype::cChainGunPrototype(const RWS::CAttributePacket &attr)
        : cCWFirearmPrototype(attr),
          m_nCaseFrameID(0xFF),
          m_nCaseExFrameID(0xFF),
          m_nBarrelFrameID(0xFF),
          m_fMaxAngVel(1200.0f),
          m_fMaxAngVelRecip(1.0f / 1200.0f),
          m_fFiringAcc(200.0f),
          m_fIdleAcc(-200.0f),
          m_fReloadAcc(-1200.0f),
          m_fExtendFraction(0.75f),
          m_fExtendSpeed(0.05f),
          m_fMaxExtend(0.05f),
          m_vecBarrelAxis(Fun_Runtime::XAxis),
          m_bAnimate(true)
    {
        m_bScale = false;
        for (tChainGunLevelData *pData = m_aChainGunLevelData; pData != m_aChainGunLevelData + 5; ++pData)
        {
            pData->m_fMinDamage = 1.0f;
            pData->m_fMaxDamage = 50.0f;
            pData->m_fMinDuration = 1.0f / 15.0f;
            pData->m_fMaxDuration = 0.75f;
        }
    }

    float cChainGun::RetBulletDamageOverride()
    {
        const tChainGunLevelData *pLevelData = RetLevelData();
        return pLevelData->m_fMinDamage + (pLevelData->m_fMaxDamage - pLevelData->m_fMinDamage) *
            RetChainGunPrototype()->m_fMaxAngVelRecip * m_fBarrelSpeed;
    }
}
