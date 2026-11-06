// src/cTeleporterDoor.cpp
//
// Class: cTeleporterDoor (namespace: unknown). Set up automatically: no function is matched yet. The address range and
// the evidence for it are in config/splits.txt; the class is not in RuffKing.
//
// No reference layout: the class is in neither later build, so its layout comes from CD2's code alone.
//
// Declare the class in a header under include/, marked as a stand-in with its evidence, and reuse the shared headers in
// include/ for any of its bases already declared there; read docs/matching-notes.md first. The open functions:
//     py -I tools/cd2.py tasks src/cTeleporterDoor.cpp

#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cPrismaticProp.h"
#include "rws/classfactory.h"
#include "unknown/cTeleporterDoor.h"
#include "cd2/memory.h"

namespace unknown
{
    const Fun_Runtime::cClass *cTeleporterDoor::ms_pcTeleporterDoorClass = &cTeleporterDoor::StaticCreateClass();

    Fun_Runtime::cClass &cTeleporterDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTeleporterDoorClass = new Fun_Runtime::cClass(0x1022, "cTeleporterDoor", 0xEF0);
        return *cTeleporterDoorClass;
    }

    static RWS::CClassFactory::CRegistrar cTeleporterDoorRegistrar(
        "cTeleporterDoor", cTeleporterDoor::MakeNew, 0xEF0, false);

    // CD2 0x82FF9918: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTeleporterDoorcPrismaticPropInheritRegistrar(
        unknown::cTeleporterDoor::StaticCreateClass(), Prop::cPrismaticProp::StaticCreateClass());

    // CD2 0x82FF99D0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cTeleporterDoorSpawningRegistrar(
        cTeleporterDoor::StaticCreateClass(), cTeleporterDoor::SpawnFromPrototype);

    RWS::CAttributeHandler *cTeleporterDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTeleporterDoorPrototype(packet);
    }

    const char *cTeleporterDoor::RetClassName() const
    {
        return "cTeleporterDoor";
    }

    // CD2 0x82740B40 has no derived cleanup beyond vtable restoration.
    cTeleporterDoor::~cTeleporterDoor()
    {
    }
}
