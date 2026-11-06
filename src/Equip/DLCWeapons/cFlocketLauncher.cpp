// src/Equip/DLCWeapons/cFlocketLauncher.cpp
//
// Class: cFlocketLauncher (namespace: Equip). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cFlocketLauncher.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/DLCWeapons/cFlocketLauncher.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/DLCWeapons/cFlocketLauncher.cpp

#include "Equip/cCWHeavyWeapon.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Equip/cFlocketLauncher.h"
#include "cd2/memory.h"
#include <new>

namespace Equip
{
    const Fun_Runtime::cClass *cFlocketLauncher::ms_pcFlocketLauncherClass = &cFlocketLauncher::StaticCreateClass();

    RWS::CAttributeHandler *cFlocketLauncher::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cFlocketLauncher;
        return 0;
    }

    Fun_Runtime::cClass &cFlocketLauncher::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cFlocketLauncherClass = new Fun_Runtime::cClass(0x605F, "cFlocketLauncher", 0xA30);
        return *cFlocketLauncherClass;
    }

    static RWS::CClassFactory::CRegistrar cFlocketLauncherRegistrar(
        "cFlocketLauncher", cFlocketLauncher::MakeNew, 0xA30, false);

    // CD2 0x82FD33B0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cFlocketLauncherSpawningRegistrar(
        cFlocketLauncher::StaticCreateClass(), cFlocketLauncher::SpawnFromPrototype);

    // CD2 0x82FD32F8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cFlocketLaunchercCWHeavyWeaponInheritRegistrar(
        Equip::cFlocketLauncher::StaticCreateClass(), Equip::cCWHeavyWeapon::StaticCreateClass());

    const char *cFlocketLauncher::RetClassName() const
    {
        return "cFlocketLauncher";
    }

    const Fun_Runtime::cClass &cFlocketLauncher::RetClass() const
    {
        return *ms_pcFlocketLauncherClass;
    }

    bool cFlocketLauncher::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcFlocketLauncherClass->IsA(c);
    }

    // CD2 0x82630FF0 has no derived cleanup beyond vtable restoration.
    cFlocketLauncher::~cFlocketLauncher()
    {
    }
}
