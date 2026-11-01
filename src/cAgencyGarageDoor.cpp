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
