// src/Equip/Gadget/cRealNadeLauncher.cpp
//
// Class: cRealNadeLauncher (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cRealNadeLauncher.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Gadget/cRealNadeLauncher.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Gadget/cRealNadeLauncher.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "fun_runtime/retval.h"
#include "Equip/cCWHeavyWeapon.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cRealNadeLauncher.h"
#include "cd2/memory.h"
#include <new>

namespace Equip
{
    const Fun_Runtime::cClass *cRealNadeLauncher::ms_pcRealNadeLauncherClass = &cRealNadeLauncher::StaticCreateClass();

    RWS::CAttributeHandler *cRealNadeLauncher::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cRealNadeLauncher;
        return 0;
    }

    Fun_Runtime::cClass &cRealNadeLauncher::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRealNadeLauncherClass = new Fun_Runtime::cClass(0x6067, "cRealNadeLauncher", 0xA20);
        return *cRealNadeLauncherClass;
    }

    static RWS::CClassFactory::CRegistrar cRealNadeLauncherRegistrar(
        "cRealNadeLauncher", cRealNadeLauncher::MakeNew, 0xA20, false);

    // CD2 0x82FD3B80: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cRealNadeLauncherSpawningRegistrar(
        cRealNadeLauncher::StaticCreateClass(), cRealNadeLauncher::SpawnFromPrototype);

    // CD2 0x82FD3AC8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cRealNadeLaunchercCWHeavyWeaponInheritRegistrar(
        Equip::cRealNadeLauncher::StaticCreateClass(), Equip::cCWHeavyWeapon::StaticCreateClass());

    const char *cRealNadeLauncher::RetClassName() const
    {
        return "cRealNadeLauncher";
    }

    const Fun_Runtime::cClass &cRealNadeLauncher::RetClass() const
    {
        return *ms_pcRealNadeLauncherClass;
    }

    bool cRealNadeLauncher::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcRealNadeLauncherClass->IsA(c);
    }

    // CD2 0x82634BE8 has no derived cleanup beyond vtable restoration.
    cRealNadeLauncher::~cRealNadeLauncher()
    {
    }

    Fun_Runtime::RetVal cRealNadeLauncher::cRealNadeLauncherPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
