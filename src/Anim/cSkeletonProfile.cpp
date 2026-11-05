#include "fun_runtime/inheritance_registrar.h"
#include "gom/non_game_base.h"
#include "Anim/cSkeletonProfile.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"

namespace Anim
{
    const char *cSkeletonProfile::RetClassName() const
    {
        return "cSkeletonProfile";
    }

    static RWS::CClassFactory::CRegistrar cSkeletonProfileRegistrar(
        "cSkeletonProfile", cSkeletonProfile::MakeNew, 0x190, false);

    Fun_Runtime::cClass &cSkeletonProfile::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSkeletonProfileClass = new Fun_Runtime::cClass(0x5EF, "cSkeletonProfile", 0x190);
        return *cSkeletonProfileClass;
    }

    const Fun_Runtime::cClass *cSkeletonProfile::ms_pcSkeletonProfileClass = &cSkeletonProfile::StaticCreateClass();

    const Fun_Runtime::cClass &cSkeletonProfile::RetClass() const
    {
        return *ms_pcSkeletonProfileClass;
    }

    bool cSkeletonProfile::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcSkeletonProfileClass->IsA(c);
    }

    // CD2 0x82FA0930: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cSkeletonProfilecNonGameBaseInheritRegistrar(
        Anim::cSkeletonProfile::StaticCreateClass(), cNonGameBase::StaticCreateClass());

    // CD2 0x824E6810: the class-factory constructor; the constructor stays out of line.
    RWS::CAttributeHandler *cSkeletonProfile::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cSkeletonProfile(packet);
    }
}
