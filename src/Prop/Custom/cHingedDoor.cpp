#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cHingedProp.h"
#include "Prop/cHingedDoor.h"
#include <new>
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "fun_runtime/script_type_registrar.h"

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

    static RWS::CClassFactory::CRegistrar cHingedDoorRegistrar(
        "cHingedDoor", cHingedDoor::MakeNew, 0xEE0, false);

    Fun_Runtime::cClass &cHingedDoor::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cHingedDoorClass = new Fun_Runtime::cClass(0x13881, "cHingedDoor", 0xEE0);
        return *cHingedDoorClass;
    }

    const Fun_Runtime::cClass *cHingedDoor::ms_pcHingedDoorClass = &cHingedDoor::StaticCreateClass();

    // CD2 0x82FFAEF0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cHingedDoorcHingedPropInheritRegistrar(
        Prop::cHingedDoor::StaticCreateClass(), Prop::cHingedProp::StaticCreateClass());

    // CD2 0x82FFAFA8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cHingedDoorSpawningRegistrar(
        cHingedDoor::StaticCreateClass(), cHingedDoor::SpawnFromPrototype);

    // CD2 script-type registration; constructor/table evidence identifies the child and parent.
    static Fun_Runtime::cScriptTypeRegistrar<cHingedDoor> cHingedDoorScriptRegistrar(
        "cHingedDoor", "cHingedProp");

    const Fun_Runtime::cScriptTypeRegistration *cHingedDoor::RetScriptTypeRegistration() const
    {
        return &cHingedDoorScriptRegistrar;
    }
}
