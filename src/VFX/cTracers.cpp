#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "VFX/cTracers.h"

namespace VFX
{
    const char *cTracers::RetClassName() const
    {
        return "cTracers";
    }
}

#include "cd2/memory.h"

namespace VFX
{
    Fun_Runtime::cClass &cTracers::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTracersClass = new Fun_Runtime::cClass(0x1F97D, "cTracers", 0x138);
        return *cTracersClass;
    }
}

namespace VFX
{
    const Fun_Runtime::cClass *cTracers::ms_pcTracersClass = &cTracers::StaticCreateClass();
}

namespace VFX
{
    static RWS::CClassFactory::CRegistrar cTracersRegistrar(
        "cTracers", cTracers::MakeNew, 0x138, false);
}

// CD2 0x83008808: runtime class inheritance registration.
namespace VFX
{
    static Fun_Runtime::cInheritanceRegistrar cTracerscNonGameBaseInheritRegistrar(
        VFX::cTracers::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

// CD2 0x827B9928: the class-factory constructor; the constructor stays out of line.
namespace VFX
{
    RWS::CAttributeHandler *cTracers::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTracers;
    }
}
