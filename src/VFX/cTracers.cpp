// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "rws/classfactory.h"
#include "VFX/cTracers.h"
#include "cd2/memory.h"

namespace VFX
{
    const char *cTracers::RetClassName() const
    {
        return "cTracers";
    }

    Fun_Runtime::cClass &cTracers::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTracersClass = new Fun_Runtime::cClass(0x1F97D, "cTracers", 0x138);
        return *cTracersClass;
    }

    const Fun_Runtime::cClass *cTracers::ms_pcTracersClass = &cTracers::StaticCreateClass();

    static RWS::CClassFactory::CRegistrar cTracersRegistrar(
        "cTracers", cTracers::MakeNew, 0x138, false);

    // CD2 0x83008808: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cTracerscNonGameBaseInheritRegistrar(
        VFX::cTracers::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x827B9928: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cTracers::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cTracers;
    }
}
