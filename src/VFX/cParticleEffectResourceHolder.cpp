// src/VFX/cParticleEffectResourceHolder.cpp
//
// Class: cParticleEffectResourceHolder (namespace: VFX). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cParticleEffectResource.obj.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/VFX/cParticleEffectResourceHolder.cpp

#include "rws/classfactory.h"
#include "VFX/cParticleEffectResourceHolder.h"
#include "cd2/memory.h"
#include "VFX/cParticleEffectManager.h"

namespace VFX
{
    cParticleEffectResourceHolder::~cParticleEffectResourceHolder()
    {
        for (unsigned int i = 0; i < m_vResources.size(); ++i)
            cParticleEffectManager::UnregisterParticleEffectResource(m_vResources[i]);
    }

    const Fun_Runtime::cClass &cParticleEffectResourceHolder::RetClass() const
    {
        return *ms_pcParticleEffectResourceHolderClass;
    }

    bool cParticleEffectResourceHolder::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcParticleEffectResourceHolderClass->IsA(testClass);
    }

    RWS::CAttributeHandler *cParticleEffectResourceHolder::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cParticleEffectResourceHolder(packet);
    }

    // CD2 0x827EDC28.
    const char *cParticleEffectResourceHolder::RetClassName() const
    {
        return "cParticleEffectResourceHolder";
    }

    // CD2 0x830099C0 (initializer) and 0x83042970 (at-exit destructor).
    static RWS::CClassFactory::CRegistrar cParticleEffectResourceHolderRegistrar(
        "cParticleEffectResourceHolder", cParticleEffectResourceHolder::MakeNew, 0x90, false);
}
