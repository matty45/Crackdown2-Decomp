// src/WorldManager/cStaticEnvironment.cpp
//
// Class: cStaticEnvironment (namespace: WorldManager). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; RuffKing's object for it is cStaticEnvironment1.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/WorldManager/cStaticEnvironment.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/WorldManager/cStaticEnvironment.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cStaticBody.h"
#include "rws/classfactory.h"
#include "WorldManager/cStaticEnvironment.h"
#include "cd2/memory.h"
#include "rws/CResource.h"

namespace WorldManager
{
    const Fun_Runtime::cClass *cStaticEnvironment::ms_pcStaticEnvironmentClass = &cStaticEnvironment::StaticCreateClass();

    const Fun_Runtime::cClass &cStaticEnvironment::RetClass() const
    {
        return *ms_pcStaticEnvironmentClass;
    }

    bool cStaticEnvironment::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcStaticEnvironmentClass->IsA(c);
    }

    RWS::CAttributeHandler *cStaticEnvironment::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cStaticEnvironment(packet);
    }

    Fun_Runtime::cClass &cStaticEnvironment::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cStaticEnvironmentClass = new Fun_Runtime::cClass(0x3, "cStaticEnvironment", 0x2E0);
        return *cStaticEnvironmentClass;
    }

    static RWS::CClassFactory::CRegistrar cStaticEnvironmentRegistrar(
        "cStaticEnvironment", cStaticEnvironment::MakeNew, 0x2E0, false);

    // CD2 0x8300CB78: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cStaticEnvironmentcStaticBodyInheritRegistrar(
        WorldManager::cStaticEnvironment::StaticCreateClass(), PHYSICS::cStaticBody::StaticCreateClass());

    const char *cStaticEnvironment::RetClassName() const
    {
        return "cStaticEnvironment";
    }

    unsigned char cStaticEnvironment::RetResourceState()
    {
        return m_nResourceState;
    }

    void cStaticEnvironment::TermClump()
    {
        cGameBase::TermClump();
    }
}

// CD2 folds the shared base implementation into this translation unit.
void cGameBase::TickUpdate(float)
{
    if (m_nNGBFlags & 1)
        ++m_nTickCount;
    vf138();
}

namespace WorldManager
{
    void cStaticEnvironment::ReCalculateResourceState()
    {
        m_nResourceState = 0x3F;
        if (m_apResources[1] && static_cast<RWS::CResource *>(m_apResources[1])->RetLoadingStatus() != 0)
            m_nResourceState &= ~2;
        if (m_apResources[2] && static_cast<RWS::CResource *>(m_apResources[2])->RetLoadingStatus() != 0)
            m_nResourceState &= ~4;
        if (m_apResources[3] && static_cast<RWS::CResource *>(m_apResources[3])->RetLoadingStatus() != 0)
            m_nResourceState &= ~8;
        if (m_apResources[0] && static_cast<RWS::CResource *>(m_apResources[0])->RetLoadingStatus() != 0)
            m_nResourceState &= ~1;
    }

    bool cStaticEnvironment::HasLoadedResources(eResourcesType resources)
    {
        return (m_nResourceState & resources) != 0;
    }
}
