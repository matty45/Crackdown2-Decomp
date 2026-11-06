// src/cPopulationZone.cpp
//
// Class: cPopulationZone (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cPopulationZone.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "unknown/cPopulationZone.h"
#include "cd2/memory.h"
#include "fun_runtime/inheritance_registrar.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cPopulationZonecZoneInheritRegistrar(
        cPopulationZone::StaticCreateClass(), cZone::StaticCreateClass());

    GangManager::cGangInfo *cPopulationZone::RetGangInControl() const
    {
        return m_pGangInControl;
    }

    void cPopulationZone::SetGangInControl(GangManager::cGangInfo *gang)
    {
        m_pGangInControl = gang;
        if (!m_pInitialGangInControl)
            m_pInitialGangInControl = gang;
    }

    cPopulationZone::~cPopulationZone()
    {
        m_pGangInControl = 0;
        m_pInitialGangInControl = 0;
    }

    void cPopulationZone::SetInitialGangInControl(GangManager::cGangInfo *gang)
    {
        m_pInitialGangInControl = gang;
        if (!m_pGangInControl)
            m_pGangInControl = gang;
    }

    const Fun_Runtime::cClass *cPopulationZone::ms_pcPopulationZoneClass = &cPopulationZone::StaticCreateClass();

    Fun_Runtime::cClass &cPopulationZone::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPopulationZoneClass = new Fun_Runtime::cClass(0x416, "cPopulationZone", 0x150);
        return *cPopulationZoneClass;
    }

    static RWS::CClassFactory::CRegistrar cPopulationZoneRegistrar(
        "cPopulationZone", cPopulationZone::MakeNew, 0x150, false);

    const Fun_Runtime::cClass &cPopulationZone::RetClass() const
    {
        return *ms_pcPopulationZoneClass;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cPopulationZone> cPopulationZoneScriptRegistrar(
        "cPopulationZone", "cScriptHost");

    bool cPopulationZone::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPopulationZoneClass->IsA(c);
    }

    const Fun_Runtime::cScriptTypeRegistration *cPopulationZone::RetScriptTypeRegistration() const
    {
        return &cPopulationZoneScriptRegistrar;
    }
}
