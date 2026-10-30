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
