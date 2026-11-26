// src/Equip/Gadget/cPulseRifle.cpp
//
// Class: cPulseRifle (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cPulseRifle.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cPulseRifle.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cPulseRifle.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Equip/cCWWeapon.h"
#include "rws/classfactory.h"
#include "Equip/cPulseRifle.h"
#include "cd2/memory.h"
#include "Havok/hkAabbPhantom.h"
#include "PHYSICS/cPhysicsWorld.h"
#include "rws/time.h"
#include "VFX/cParticleEffectInstance.h"
#include "CHARACTER/cCharacter.h"
#include "Vehicle/cVehicle.h"

namespace Equip
{
    const Fun_Runtime::cClass *cPulseRifle::ms_pcPulseRifleClass = &cPulseRifle::StaticCreateClass();

    const Fun_Runtime::cClass &cPulseRifle::RetClass() const
    {
        return *ms_pcPulseRifleClass;
    }

    bool cPulseRifle::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPulseRifleClass->IsA(c);
    }

    Fun_Runtime::cClass &cPulseRifle::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPulseRifleClass = new Fun_Runtime::cClass(0x27413, "cPulseRifle", 0xA80);
        return *cPulseRifleClass;
    }

    static RWS::CClassFactory::CRegistrar cPulseRifleRegistrar(
        "cPulseRifle", cPulseRifle::MakeNew, 0xA80, false);

    // CD2 0x82FCD220: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPulseRiflecCWWeaponInheritRegistrar(
        Equip::cPulseRifle::StaticCreateClass(), Equip::cCWWeapon::StaticCreateClass());

    // CD2 0x82FCD2D8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPulseRifleSpawningRegistrar(
        cPulseRifle::StaticCreateClass(), cPulseRifle::SpawnFromPrototype);

    RWS::CAttributeHandler *cPulseRifle::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPulseRiflePrototype(packet);
    }

    const char *cPulseRifle::RetClassName() const
    {
        return "cPulseRifle";
    }

    RWS::CAttributeHandler *cPulseRifle::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPulseRifle;
        return 0;
    }

    Fun_Runtime::RetVal cPulseRifle::cPulseRiflePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    cPulse::cPulse()
        : m_pProfile(NULL), m_vPosition(Fun_Runtime::ZeroVec), m_vDirection(Fun_Runtime::ZAxis), m_fStartTime(0.0f),
          m_pPhantom(NULL), m_pPulseVFX(NULL), m_bActive(false)
    {
        m_vCollected.clear();
    }

    cPulse::~cPulse()
    {
        Stop();
    }

    void cPulse::Update()
    {
        if (m_bActive)
        {
            if (RWS::Time::RetGameTimeSecs() < m_fStartTime + m_pProfile->fPulseDuration)
            {
                if (m_pPhantom)
                    PHYSICS::cPhysicsUniverse::FindBodiesInAabb(m_pPhantom, *this);
                UpdatePulseVFX();
            }
            else
                Stop();
        }
    }

    void cPulse::Stop()
    {
        m_fStartTime = 0.0f;
        if (m_pPhantom)
        {
            PHYSICS::cPhysicsUniverse::m_pPrimaryWorld->removePhantom(m_pPhantom);
            m_pPhantom->removeReference();
            m_pPhantom = NULL;
        }
        m_vCollected.clear();
        ReleasePulseVFX();
        m_bActive = false;
    }

    void cPulse::ReleasePulseVFX()
    {
        if (m_pPulseVFX)
        {
            m_pPulseVFX->StopEmitters();
            m_pPulseVFX->SetAsOrphan();
            m_pPulseVFX->Release();
            m_pPulseVFX = NULL;
        }
    }

    tPulseTargetProfile &cPulse::RetPulseTargetProfile(PHYSICS::cBody *pBody) const
    {
        if (pBody->IsA(*CHARACTER::cCharacter::ms_pcCharacterClass))
            return m_pProfile->aTargetProfiles[2];
        if (pBody->IsA(*Vehicle::cVehicle::ms_pcVehicleClass))
            return m_pProfile->aTargetProfiles[1];
        if (pBody->IsA(*cEquipment::ms_pcEquipmentClass))
            return m_pProfile->aTargetProfiles[3];
        return m_pProfile->aTargetProfiles[0];
    }

    void cPulseRifle::TickUpdate(float fDeltaTime)
    {
        cCWWeapon::TickUpdate(fDeltaTime);
        if (m_Pulse.IsActive())
            m_Pulse.Update();
    }
}
