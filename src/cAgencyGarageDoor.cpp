#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cSlidingDoor.h"
#include "unknown/cAgencyGarageDoor.h"
#include "rws/classfactory.h"

namespace unknown
{
    const char *cAgencyGarageDoor::RetClassName() const
    {
        return "cAgencyGarageDoor";
    }
}

namespace unknown
{
    static RWS::CClassFactory::CRegistrar cAgencyGarageDoorRegistrar(
        "cAgencyGarageDoor", cAgencyGarageDoor::MakeNew, 0xF30, false);
}

#include "cd2/memory.h"

namespace unknown
{
    Fun_Runtime::cClass &cAgencyGarageDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgencyGarageDoorClass = new Fun_Runtime::cClass(0x1023, "cAgencyGarageDoor", 0xF30);
        return *cAgencyGarageDoorClass;
    }
}

namespace unknown
{
    const Fun_Runtime::cClass *cAgencyGarageDoor::ms_pcAgencyGarageDoorClass = &cAgencyGarageDoor::StaticCreateClass();
}

// CD2 0x82FF67B0: runtime class inheritance registration.
namespace unknown
{
    static Fun_Runtime::cInheritanceRegistrar cAgencyGarageDoorcSlidingDoorInheritRegistrar(
        unknown::cAgencyGarageDoor::StaticCreateClass(), Prop::cSlidingDoor::StaticCreateClass());
}

#include <new>

// CD2 0x82732E48: placement factory; the constructor stays out of line (a tail call).
namespace unknown
{
    RWS::CAttributeHandler *cAgencyGarageDoor::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) cAgencyGarageDoor(prototype);
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82FF6868: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace unknown
{
    static GOM::cProtoRegistrar cAgencyGarageDoorSpawningRegistrar(
        cAgencyGarageDoor::StaticCreateClass(), cAgencyGarageDoor::SpawnFromPrototype);
}

// CD2 0x82732DC0: the class factory builds the prototype.
namespace unknown
{
    RWS::CAttributeHandler *cAgencyGarageDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgencyGarageDoorPrototype(packet);
    }
}
