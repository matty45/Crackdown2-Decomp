#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "Prop/cProp.h"
// The shared cProp hierarchy now reproduces the inherited vptr stores exactly.
#include "Prop/cPintleFaceplate.h"
#include "Prop/cPintleFaceplatePrototype.h"
#include <new>
#include "rws/classfactory.h"

namespace Prop
{
    RWS::CAttributeHandler *cPintleFaceplate::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPintleFaceplatePrototype(packet);
    }

    Fun_Runtime::RetVal cPintleFaceplatePrototype::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }

    // CD2 0x827453D8 has no derived cleanup beyond vtable restoration.
    cPintleFaceplate::~cPintleFaceplate()
    {
    }

    const char *cPintleFaceplate::RetClassName() const
    {
        return "cPintleFaceplate";
    }
}

namespace Prop
{
    static RWS::CClassFactory::CRegistrar cPintleFaceplateRegistrar(
        "cPintleFaceplate", cPintleFaceplate::MakeNew, 0xE40, false);
}

#include "cd2/memory.h"

namespace Prop
{
    Fun_Runtime::cClass &cPintleFaceplate::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPintleFaceplateClass = new Fun_Runtime::cClass(0xD439, "cPintleFaceplate", 0xE40);
        return *cPintleFaceplateClass;
    }
}

namespace Prop
{
    const Fun_Runtime::cClass *cPintleFaceplate::ms_pcPintleFaceplateClass = &cPintleFaceplate::StaticCreateClass();

    const Fun_Runtime::cClass &cPintleFaceplate::RetClass() const
    {
        return *ms_pcPintleFaceplateClass;
    }
}

namespace Prop
{
    bool cPintleFaceplate::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPintleFaceplateClass->IsA(c);
    }
}

// CD2 0x82FFB668: runtime class inheritance registration.
namespace Prop
{
    static Fun_Runtime::cInheritanceRegistrar cPintleFaceplatecPropInheritRegistrar(
        Prop::cPintleFaceplate::StaticCreateClass(), Prop::cProp::StaticCreateClass());
}

// CD2 0x82FFB720: register the class descriptor and placement factory.
namespace Prop
{
    static GOM::cProtoRegistrar cPintleFaceplateSpawningRegistrar(
        cPintleFaceplate::StaticCreateClass(), cPintleFaceplate::SpawnFromPrototype);
}
