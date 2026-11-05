#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cSlidingDoor.h"
#include "unknown/cAgencyGarageDoor.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace unknown
{
    const char *cAgencyGarageDoor::RetClassName() const
    {
        return "cAgencyGarageDoor";
    }

    static RWS::CClassFactory::CRegistrar cAgencyGarageDoorRegistrar(
        "cAgencyGarageDoor", cAgencyGarageDoor::MakeNew, 0xF30, false);

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
