#include "fun_runtime/retval.h"
#include "PHYSICS/cSurfaceProfile.h"
#include "rws/classfactory.h"
#include "fun_runtime/inheritance_registrar.h"

namespace PHYSICS
{
    // CD2 0x82FE20C8 registers cNonGameBase before the derived runtime class.
    static Fun_Runtime::cInheritanceRegistrar cSurfaceProfilecNonGameBaseInheritRegistrar(
        cSurfaceProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    RWS::CAttributeHandler *cSurfaceProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cSurfaceProfile;
    }

    const char *cSurfaceProfile::RetClassName() const
    {
        return "cSurfaceProfile";
    }
}

namespace PHYSICS
{
    static RWS::CClassFactory::CRegistrar cSurfaceProfileRegistrar(
        "cSurfaceProfile", cSurfaceProfile::MakeNew, 0x80, false);
}

#include "cd2/memory.h"

namespace PHYSICS
{
    Fun_Runtime::cClass &cSurfaceProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSurfaceProfileClass = new Fun_Runtime::cClass(0xA8C, "cSurfaceProfile", 0x80);
        return *cSurfaceProfileClass;
    }
}

namespace PHYSICS
{
    const Fun_Runtime::cClass *cSurfaceProfile::ms_pcSurfaceProfileClass = &cSurfaceProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cSurfaceProfile::RetClass() const
    {
        return *ms_pcSurfaceProfileClass;
    }
}

namespace PHYSICS
{
    bool cSurfaceProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSurfaceProfileClass->IsA(c);
    }
}

namespace PHYSICS
{
    Fun_Runtime::RetVal cSurfaceProfile::Init(const RWS::CAttributePacket &)
    {
        return Ret_OK;
    }
}
