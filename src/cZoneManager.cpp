// src/cZoneManager.cpp
//
// Class: cZoneManager (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cZoneManager.cpp

#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "unknown/cZoneManager.h"
#include "rws/logic.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    bool cZoneManager::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcZoneManagerClass->IsA(testClass);
    }

    cZoneManager::~cZoneManager()
    {
        if (m_pPopulationZonePool)
        {
            delete m_pPopulationZonePool;
            m_pPopulationZonePool = 0;
        }
        ms_pInstance = 0;
        UnLinkMsg(RWS::iMsgRunningTick);
    }

    cZoneManager *cZoneManager::ms_pInstance;

    cZoneManager *cZoneManager::RetInstance()
    {
        return ms_pInstance;
    }

    const Fun_Runtime::cClass *cZoneManager::ms_pcZoneManagerClass = &cZoneManager::StaticCreateClass();

    Fun_Runtime::cClass &cZoneManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cZoneManagerClass = new Fun_Runtime::cClass(0x60E, "cZoneManager", 0x84);
        return *cZoneManagerClass;
    }

    static RWS::CClassFactory::CRegistrar cZoneManagerRegistrar(
        "cZoneManager", cZoneManager::MakeNew, 0x84, false);

    // CD2 0x8300D808: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cZoneManagercNonGameBaseInheritRegistrar(
        unknown::cZoneManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x8300D870: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cZoneManagercDebugPageHandlerInheritRegistrar(
        unknown::cZoneManager::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    const char *cZoneManager::RetClassName() const
    {
        return "cZoneManager";
    }

    const Fun_Runtime::cClass &cZoneManager::RetClass() const
    {
        return *ms_pcZoneManagerClass;
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cZoneManager> cZoneManagerScriptRegistrar(
        "cZoneManager", "cNonGameBase");

    const Fun_Runtime::cScriptTypeRegistration *cZoneManager::RetScriptTypeRegistration() const
    {
        return &cZoneManagerScriptRegistrar;
    }

    RWS::CAttributeHandler *cZoneManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cZoneManager;
    }
}
