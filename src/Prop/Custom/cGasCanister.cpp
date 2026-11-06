// src/Prop/Custom/cGasCanister.cpp
//
// Class: cGasCanister (namespace: Prop). The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cGasCanister.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/Custom/cGasCanister.h.
//
// Open functions:
//     py -I tools/cd2.py tasks src/Prop/Custom/cGasCanister.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "rws/classfactory.h"
#include "Prop/cGasCanister.h"
#include "Prop/cGasCanisterPrototype.h"
#include "gom/proto_registrar.h"
#include "Activity/cActivityManager.h"
#include "VFX/cParticleEffectManager.h"
#include "rw/rwmem.h"
#include <new>

namespace Prop
{
    void cGasCanisterPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPropPrototype::HandleAttributes(packet);
        for (RWS::CAttributeCommandIterator it(packet, "cGasCanister"); !it.IsFinished(); ++it)
        {
            switch (it->GetCommandId())
            {
            case 0:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, 4);
                    m_fAcceleration = value;
                }
                break;
            case 1:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, 4);
                    m_fMaxForwardSpeed = value;
                }
                break;
            case 2:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, 4);
                    m_fRocketDuration = value;
                }
                break;
            case 3:
                m_nPlumeVFX = VFX::g_pParticleEffectManager->RetEffectId(it->GetAs_char_ptr());
                break;
            // CD2 lays out the valve-radius arm before the plume-scale arm.
            case 5:
                {
                    float radius = it->GetAs_float();
                    RwMemNative32(&radius, 4);
                    m_fValveRadiusSq = radius * radius;
                }
                break;
            case 4:
                {
                    float value = it->GetAs_float();
                    RwMemNative32(&value, 4);
                    m_fPlumeScale = value;
                }
                break;
            }
        }
    }

    cGasCanister::cGasCanister(GOM::cObjectPrototype *prototype)
        : cProp(prototype), m_fRocketTimer(0.0f)
    {
        m_nCState = CS_FULL_O_GAS;
        m_nNumKillsForLocalPlayer = 0;
        m_bFuseAudioPlayed = false;
    }

    Fun_Runtime::RetVal cGasCanister::Term()
    {
        m_nNumKillsForLocalPlayer = 0;
        return cProp::Term();
    }

    void cGasCanister::NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char)
    {
        m_nCState = CS_DEPLETED;
        Activity::cActivityManager::RetActivityManager().RequestDelete(this);
    }

    RWS::CAttributeHandler *cGasCanister::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGasCanisterPrototype(packet);
    }

    const char *cGasCanister::RetClassName() const
    {
        return "cGasCanister";
    }

    static RWS::CClassFactory::CRegistrar cGasCanisterRegistrar(
        "cGasCanister", cGasCanister::MakeNew, 0xe40, false);
    static GOM::cProtoRegistrar cGasCanisterSpawningRegistrar(
        cGasCanister::StaticCreateClass(), cGasCanister::SpawnFromPrototype);

    RWS::CAttributeHandler *cGasCanister::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cGasCanister(prototype);
        return 0;
    }
}
