// src/cDebugPlayer.cpp
//
// Class: cDebugPlayer (namespace: unknown). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cDebugPlayer.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "unknown/cDebugPlayer.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cDebugPlayer::ms_pcDebugPlayerClass = &cDebugPlayer::StaticCreateClass();

    Fun_Runtime::cClass &cDebugPlayer::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cDebugPlayerClass = new Fun_Runtime::cClass(0x63D, "cDebugPlayer", 0x190);
        return *cDebugPlayerClass;
    }

    static RWS::CClassFactory::CRegistrar cDebugPlayerRegistrar(
        "cDebugPlayer", cDebugPlayer::MakeNew, 0x190, false);

    // CD2 0x82FF2CD8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cDebugPlayercNonGameBaseInheritRegistrar(
        unknown::cDebugPlayer::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    const char *cDebugPlayer::RetClassName() const
    {
        return "cDebugPlayer";
    }

    const Fun_Runtime::cClass &cDebugPlayer::RetClass() const
    {
        return *ms_pcDebugPlayerClass;
    }

    bool cDebugPlayer::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcDebugPlayerClass->IsA(c);
    }

    // CD2 0x82714730.
    cDebugPlayer::~cDebugPlayer()
    {
        Term();
    }

    RWS::CAttributeHandler *cDebugPlayer::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cDebugPlayer;
    }
}
