// src/Equip/Weapon/cGrenade.cpp
//
// Class: cGrenade (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cGrenade.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/Weapon/cGrenade.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/Weapon/cGrenade.cpp

// CD2 0x82FCFF88: class descriptor and placement factory.

#include "cd2/memory.h"
#include "Equip/cGrenade.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/script_type_registrar.h"
#include "rws/classfactory.h"

namespace Equip
{
    // CD2 0x82FCFF38: register the class factory.
    static RWS::CClassFactory::CRegistrar cGrenadeRegistrar(
        "cGrenade", cGrenade::MakeNew, 0x9C0, false);

    static GOM::cProtoRegistrar cGrenadeSpawningRegistrar(
        cGrenade::StaticCreateClass(), cGrenade::SpawnFromPrototype);

    RWS::CAttributeHandler *cGrenade::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cGrenadePrototype(packet);
    }

    const char *cGrenade::RetClassName() const
    {
        return "cGrenade";
    }

    RWS::CAttributeHandler *cGrenade::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cGrenade;
        return 0;
    }

    // CD2 script-type registration names this child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cGrenade> cGrenadeScriptRegistrar(
        "cGrenade", "cWeapon");

    Fun_Runtime::cClass &cGrenade::StaticCreateClass()
    {
        static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x3E8A, "cGrenade", 0x9C0);
        return *descriptor;
    }

    const Fun_Runtime::cClass *cGrenade::ms_pcGrenadeClass = &cGrenade::StaticCreateClass();

    const Fun_Runtime::cClass &cGrenade::RetClass() const
    {
        return *ms_pcGrenadeClass;
    }

    const Fun_Runtime::cScriptTypeRegistration *cGrenade::RetScriptTypeRegistration() const
    {
        return &cGrenadeScriptRegistrar;
    }
}
