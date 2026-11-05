#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
// src/cScriptManager.cpp
//
// Class: cScriptManager (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cScriptManager.cpp

#include "unknown/cScriptManager.h"
#include "cd2/memory.h"

namespace unknown
{
    cScriptManager *cScriptManager::ms_pInstance;

    cScriptManager::~cScriptManager()
    {
        ms_pInstance = 0;
        RWS::CEventHandler::UnRegisterMsg(iMsgScriptManagerBeginPlay);
        RWS::CEventHandler::UnRegisterMsg(iMsgScriptManagerEndPlay);
    }
}

namespace unknown
{
    const Fun_Runtime::cClass *cScriptManager::ms_pcScriptManagerClass = &cScriptManager::StaticCreateClass();

    Fun_Runtime::cClass &cScriptManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cScriptManagerClass = new Fun_Runtime::cClass(0x60B, "cScriptManager", 0x430);
        return *cScriptManagerClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cScriptManagerRegistrar(
        "cScriptManager", cScriptManager::MakeNew, 0x430, false);
}

// CD2 0x83000E00: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cScriptManagercNonGameBaseInheritRegistrar(
        unknown::cScriptManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

namespace unknown
{
    const char *cScriptManager::RetClassName() const
    {
        return "cScriptManager";
    }
}

#include "unknown/cScriptManager.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cScriptManager> cScriptManagerScriptRegistrar(
        "cScriptManager", "cNonGameBase");
}

namespace unknown
{
    const Fun_Runtime::cScriptTypeRegistration *cScriptManager::RetScriptTypeRegistration() const
    {
        return &cScriptManagerScriptRegistrar;
    }
}

namespace unknown
{
    RWS::CAttributeHandler *cScriptManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cScriptManager;
    }
}
