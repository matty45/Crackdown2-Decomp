// src/VFX/ParticleSystem/cParticleEffectManager.cpp
//
// Class: cParticleEffectManager (namespace: VFX). Set up automatically: no function is matched yet. The address range
// and the evidence for it are in config/splits.txt; RuffKing's object for it is cParticleEffectManager.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/VFX/ParticleSystem/cParticleEffectManager.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/ParticleSystem/cParticleEffectManager.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "VFX/cParticleEffectManager.h"
#include "cd2/memory.h"

namespace VFX
{
    const char *cParticleEffectManager::RetClassName() const
    {
        return "cParticleEffectManager";
    }

    static RWS::CClassFactory::CRegistrar cParticleEffectManagerRegistrar(
        "cParticleEffectManager", cParticleEffectManager::MakeNew, 0x370, false);

    // CD2 0x827DEDB0: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cParticleEffectManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cParticleEffectManager;
    }
}
