// src/Prop/cVehicleDamageProp.cpp
//
// Class: cVehicleDamageProp (namespace: Prop). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; RuffKing's object for it is cVehicleDamageProp.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Props/cVehicleDamageProp.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Prop/cVehicleDamageProp.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "Prop/cVehicleDamageProp.h"
#include <new>

namespace Prop
{
    RWS::CAttributeHandler *cVehicleDamageProp::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleDamagePropPrototype(packet);
    }

    const char *cVehicleDamageProp::RetClassName() const
    {
        return "cVehicleDamageProp";
    }

    static RWS::CClassFactory::CRegistrar cVehicleDamagePropRegistrar(
        "cVehicleDamageProp", cVehicleDamageProp::MakeNew, 0xed0, false);

    RWS::CAttributeHandler *cVehicleDamageProp::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cVehicleDamageProp(prototype);
        return 0;
    }

    // CD2 0x82FF5EE0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cVehicleDamagePropSpawningRegistrar(
        cVehicleDamageProp::StaticCreateClass(), cVehicleDamageProp::SpawnFromPrototype);
}
