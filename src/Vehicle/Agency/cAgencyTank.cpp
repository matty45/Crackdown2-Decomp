// src/Vehicle/Agency/cAgencyTank.cpp
//
// Class: cAgencyTank (namespace: Vehicle). Set up automatically: no function is matched yet. The address range and the
// evidence for it are in config/splits.txt; RuffKing's object for it is cAgencyTank.obj.
//
// Reference layout from a later build of the same codebase (a starting point, not CD2's: verify it against CD2's code;
// refs/ is not in the public repository: maintainers provide it on request; see AGENTS.md):
// refs/ruffking_pdb_ref/DevBranches/Kingdoms/Source/Code/Libraries/Shared/Vehicle/Agency/cAgencyTank.h.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/Vehicle/Agency/cAgencyTank.cpp

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "rws/classfactory.h"
#include "Vehicle/cAgencyTank.h"
#include "cd2/memory.h"
#include <new>
#include "Vehicle/cAgencyTankPrototype.h"

namespace Vehicle
{
    const Fun_Runtime::cClass *cAgencyTank::ms_pcAgencyTankClass = &cAgencyTank::StaticCreateClass();

    Fun_Runtime::cClass &cAgencyTank::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyTankClass = new Fun_Runtime::cClass(0x120AB, "cAgencyTank", 0x3150);
        return *cAgencyTankClass;
    }

    // CD2 0x82FEC5A8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyTankcAgencyCarInheritRegistrar(
        cAgencyTank::StaticCreateClass(), cAgencyCar::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cAgencyTankRegistrar(
        "cAgencyTank", cAgencyTank::MakeNew, 0x3150, false);

    // CD2 0x82FEC660: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgencyTankSpawningRegistrar(
        cAgencyTank::StaticCreateClass(), cAgencyTank::SpawnFromPrototype);

    RWS::CAttributeHandler *cAgencyTank::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyTankPrototype(packet);
    }

    const char *cAgencyTank::RetClassName() const
    {
        return "cAgencyTank";
    }

    RWS::CAttributeHandler *cAgencyTank::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAgencyTank;
        return 0;
    }

    Fun_Runtime::RetVal cAgencyTankPrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    void cAgencyTank::ReplicateInitialFields()
    {
        cCar::ReplicateInitialFields();
        m_Turret.ReplicateInitialFields();
    }

    void cAgencyTank::ReplicateFields()
    {
        cCar::ReplicateFields();
        m_Turret.ReplicateFields(false);
    }
}
