#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cHingedProp.h"
#include "Prop/cHingedDoor.h"
#include <new>
#include "rws/classfactory.h"

namespace Prop
{
    RWS::CAttributeHandler *cHingedDoor::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cHingedDoorPrototype(packet);
    }

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

// CD2 0x82FFAEF0: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cHingedDoorcHingedPropInheritRegistrar(
        Prop::cHingedDoor::StaticCreateClass(), Prop::cHingedProp::StaticCreateClass());
}
