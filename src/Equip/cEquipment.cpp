#include "fun_runtime/inheritance_registrar.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "rws/classfactory.h"
// src/Equip/cEquipment.cpp
//
// Class: cEquipment (namespace: Equip). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cEquipment.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Equipment/cEquipment.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Equip/cEquipment.cpp

#include "Equip/cEquipment.h"
#include "cd2/memory.h"

namespace Equip
{
    const Fun_Runtime::cClass *cEquipment::ms_pcEquipmentClass = &cEquipment::StaticCreateClass();

    Fun_Runtime::cClass &cEquipment::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cEquipmentClass = new Fun_Runtime::cClass(0x6, "cEquipment", 0x870);
        return *cEquipmentClass;
    }
}

namespace Equip
{
    static RWS::CClassFactory::CRegistrar cEquipmentRegistrar(
        "cEquipment", cEquipment::MakeNew, 0x870, false);
}

// CD2 0x82FCB1E8: runtime class inheritance registration.
namespace Equip
{
    static Fun_Runtime::cInheritanceRegistrar cEquipmentcNetDynamicBodyInheritRegistrar(
        Equip::cEquipment::StaticCreateClass(), PHYSICS::cNetDynamicBody::StaticCreateClass());
}

#include <new>

// CD2 0x826046B8: placement factory; the constructor stays out of line (a tail call).
namespace Equip
{
    RWS::CAttributeHandler *cEquipment::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cEquipment;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82FCB2A0: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace Equip
{
    static GOM::cProtoRegistrar cEquipmentSpawningRegistrar(
        cEquipment::StaticCreateClass(), cEquipment::SpawnFromPrototype);
}
