#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
// src/cRenderToTextureManager.cpp
//
// Class: cRenderToTextureManager (namespace: unknown). Set up automatically: no function is matched yet. The address
// range and the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cRenderToTextureManager.cpp

#include "unknown/cRenderToTextureManager.h"

namespace unknown
{
    cRenderToTextureManager *cRenderToTextureManager::ms_pInstance;

    bool cRenderToTextureManager::IsA(const Fun_Runtime::cClass &testClass) const
    {
        return ms_pcRenderToTextureManagerClass->IsA(testClass);
    }

    cRenderToTextureManager::~cRenderToTextureManager()
    {
        ms_pInstance = 0;
    }
}

#include "cd2/memory.h"

namespace unknown
{
    RWS::CAttributeHandler *cRenderToTextureManager::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRenderToTextureManager;
    }
}

namespace unknown
{
    const Fun_Runtime::cClass *cRenderToTextureManager::ms_pcRenderToTextureManagerClass = &cRenderToTextureManager::StaticCreateClass();

    Fun_Runtime::cClass &cRenderToTextureManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRenderToTextureManagerClass = new Fun_Runtime::cClass(0xCBED, "cRenderToTextureManager", 0x98);
        return *cRenderToTextureManagerClass;
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cRenderToTextureManagerRegistrar(
        "cRenderToTextureManager", cRenderToTextureManager::MakeNew, 0x98, false);
}

// CD2 0x83007F20: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cRenderToTextureManagercNonGameBaseInheritRegistrar(
        unknown::cRenderToTextureManager::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

namespace unknown
{
    const char *cRenderToTextureManager::RetClassName() const
    {
        return "cRenderToTextureManager";
    }
}

namespace unknown
{
    const Fun_Runtime::cClass &cRenderToTextureManager::RetClass() const
    {
        return *ms_pcRenderToTextureManagerClass;
    }
}
