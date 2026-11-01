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

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cHingedDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedDoorClass = new Fun_Runtime::cClass(0x13881, "cHingedDoor", 0xEE0);
        return *cHingedDoorClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cHingedDoor::ms_pcHingedDoorClass = &cHingedDoor::StaticCreateClass();
}
