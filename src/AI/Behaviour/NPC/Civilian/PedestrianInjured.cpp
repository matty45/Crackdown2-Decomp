#include "fun_runtime/inheritance_registrar.h"
#include "AI/PedestrianGuard.h"
#include "AI/PedestrianInjured.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *PedestrianInjured::ms_pPedestrianInjuredClass = &PedestrianInjured::StaticCreateClass();

    PedestrianInjured::PedestrianInjured() {}

    const Fun_Runtime::cClass &PedestrianInjured::RetClass() const
    {
        return *ms_pPedestrianInjuredClass;
    }

    const char *PedestrianInjured::RetClassName() const
    {
        return "PedestrianInjured";
    }

    bool PedestrianInjured::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPedestrianInjuredClass->IsA(c);
    }

    RWS::CAttributeHandler *PedestrianInjured::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new PedestrianInjured();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar PedestrianInjuredRegistrar(
        "PedestrianInjured", PedestrianInjured::MakeNew, 0x130, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &PedestrianInjured::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianInjuredClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "PedestrianInjured", 0x130);
        return *PedestrianInjuredClass;
    }
}

// CD2 0x82F93230: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar PedestrianInjuredPedestrianGuardInheritRegistrar(
        AI::PedestrianInjured::StaticCreateClass(), AI::PedestrianGuard::StaticCreateClass());
}
