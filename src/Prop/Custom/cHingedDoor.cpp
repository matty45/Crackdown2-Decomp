#include "Prop/cHingedDoor.h"
#include "rws/classfactory.h"

namespace Prop
{
    const char *cHingedDoor::RetClassName() const
    {
        return "cHingedDoor";
    }
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cHingedDoorRegistrar(
        "cHingedDoor", cHingedDoor::MakeNew, 0xEE0, false);
}
