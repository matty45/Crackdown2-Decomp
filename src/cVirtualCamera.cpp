// src/cVirtualCamera.cpp
//
// Class: cVirtualCamera (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cVirtualCamera.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/game_base.h"
#include "rws/classfactory.h"
#include "unknown/cVirtualCamera.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

namespace unknown
{
    RWS::CAttributeHandler *cVirtualCamera::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cVirtualCamera;
    }

    const Fun_Runtime::cClass *cVirtualCamera::ms_pcVirtualCameraClass = &cVirtualCamera::StaticCreateClass();

    Fun_Runtime::cClass &cVirtualCamera::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVirtualCameraClass = new Fun_Runtime::cClass(0x637, "cVirtualCamera", 0xF10);
        return *cVirtualCameraClass;
    }

    static RWS::CClassFactory::CRegistrar cVirtualCameraRegistrar(
        "cVirtualCamera", cVirtualCamera::MakeNew, 0xF10, false);

    // CD2 0x82FAB6A8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cVirtualCameracGameBaseInheritRegistrar(
        unknown::cVirtualCamera::StaticCreateClass(), cGameBase::StaticCreateClass());

    // CD2 0x82FAB710: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cVirtualCameracDebugPageHandlerInheritRegistrar(
        unknown::cVirtualCamera::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());

    const char *cVirtualCamera::RetClassName() const
    {
        return "cVirtualCamera";
    }

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cVirtualCamera> cVirtualCameraScriptRegistrar(
        "cVirtualCamera", "cGameBase");

    const Fun_Runtime::cScriptTypeRegistration *cVirtualCamera::RetScriptTypeRegistration() const
    {
        return &cVirtualCameraScriptRegistrar;
    }

    void cVirtualCamera::ToggleByte4E5()
    {
        m_byte4E5 = !m_byte4E5;
    }
}
