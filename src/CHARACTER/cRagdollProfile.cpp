#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "CHARACTER/cRagdollProfile.h"
#include "rws/classfactory.h"

namespace CHARACTER
{
    const char *cRagdollProfile::RetClassName() const
    {
        return "cRagdollProfile";
    }
}

namespace CHARACTER
{
    static RWS::CClassFactory::CRegistrar cRagdollProfileRegistrar(
        "cRagdollProfile", cRagdollProfile::MakeNew, 0x3B0, false);
}

#include "cd2/memory.h"

namespace CHARACTER
{
    Fun_Runtime::cClass &cRagdollProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cRagdollProfileClass = new Fun_Runtime::cClass(0x5EE, "cRagdollProfile", 0x3B0);
        return *cRagdollProfileClass;
    }
}

namespace CHARACTER
{
    const Fun_Runtime::cClass *cRagdollProfile::ms_pcRagdollProfileClass = &cRagdollProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cRagdollProfile::RetClass() const
    {
        return *ms_pcRagdollProfileClass;
    }
}

namespace CHARACTER
{
    bool cRagdollProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcRagdollProfileClass->IsA(c);
    }
}

// CD2 0x82FB1CC8: runtime class inheritance registration.
namespace CHARACTER
{
    static Fun_Runtime::cInheritanceRegistrar cRagdollProfilecNonGameBaseInheritRegistrar(
        CHARACTER::cRagdollProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());
}

// CD2 0x82575E48: the class-factory constructor; the constructor stays out of line.
namespace CHARACTER
{
    RWS::CAttributeHandler *cRagdollProfile::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cRagdollProfile;
    }
}
