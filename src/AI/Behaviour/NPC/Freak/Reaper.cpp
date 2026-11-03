#include "fun_runtime/inheritance_registrar.h"
#include "AI/FreakBase.h"
#include "AI/Reaper.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *Reaper::ms_pReaperClass = &Reaper::StaticCreateClass();

    Reaper::Reaper() {}

    const Fun_Runtime::cClass &Reaper::RetClass() const
    {
        return *ms_pReaperClass;
    }

    const char *Reaper::RetClassName() const
    {
        return "Reaper";
    }

    bool Reaper::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pReaperClass->IsA(c);
    }

    RWS::CAttributeHandler *Reaper::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new Reaper();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar ReaperRegistrar(
        "Reaper", Reaper::MakeNew, 0x220, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &Reaper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ReaperClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Reaper", 0x220);
        return *ReaperClass;
    }
}

// CD2 0x82F93ED8: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar ReaperFreakBaseInheritRegistrar(
        AI::Reaper::StaticCreateClass(), AI::FreakBase::StaticCreateClass());
}
