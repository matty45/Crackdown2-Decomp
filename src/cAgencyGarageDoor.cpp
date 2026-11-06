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
#include "Prop/cSlidingDoor.h"
#include "unknown/cAgencyGarageDoor.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include <new>

namespace unknown
{
    RWS::CAttributeHandler *cAgencyGarageDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyGarageDoorPrototype(packet);
    }

    const char *cAgencyGarageDoor::RetClassName() const
    {
        return "cAgencyGarageDoor";
    }

    static RWS::CClassFactory::CRegistrar cAgencyGarageDoorRegistrar(
        "cAgencyGarageDoor", cAgencyGarageDoor::MakeNew, 0xF30, false);

    RWS::CAttributeHandler *cAgencyGarageDoor::SpawnFromPrototype(GOM::cObjectPrototype *pPrototype, void *pMem)
    {
        if (pMem)
            return new (pMem) cAgencyGarageDoor(pPrototype);
        return 0;
    }

    Fun_Runtime::cClass &cAgencyGarageDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyGarageDoorClass = new Fun_Runtime::cClass(0x1023, "cAgencyGarageDoor", 0xF30);
        return *cAgencyGarageDoorClass;
    }

    const Fun_Runtime::cClass *cAgencyGarageDoor::ms_pcAgencyGarageDoorClass = &cAgencyGarageDoor::StaticCreateClass();

    // CD2 0x82FF67B0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAgencyGarageDoorcSlidingDoorInheritRegistrar(
        unknown::cAgencyGarageDoor::StaticCreateClass(), Prop::cSlidingDoor::StaticCreateClass());

    // CD2 0x82FF6868: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAgencyGarageDoorSpawningRegistrar(
        cAgencyGarageDoor::StaticCreateClass(), cAgencyGarageDoor::SpawnFromPrototype);
}
