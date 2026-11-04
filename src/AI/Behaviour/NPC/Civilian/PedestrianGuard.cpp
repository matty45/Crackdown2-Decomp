#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPedestrianBase.h"
#include "AI/PedestrianGuard.h"
#include "rws/classfactory.h"

#include <new>

namespace AI
{
    PedestrianGuard::PedestrianGuard() : m_nUnknown120(0), m_nUnknown124(0) {}

    RWS::CAttributeHandler *PedestrianGuard::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) PedestrianGuard;
        return 0;
    }

    const char *PedestrianGuard::RetClassName() const
    {
        return "PedestrianGuard";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar PedestrianGuardRegistrar(
        "PedestrianGuard", PedestrianGuard::MakeNew, 0x130, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &PedestrianGuard::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianGuardClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "PedestrianGuard", 0x130);
        return *PedestrianGuardClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *PedestrianGuard::ms_pPedestrianGuardClass = &PedestrianGuard::StaticCreateClass();

    const Fun_Runtime::cClass &PedestrianGuard::RetClass() const
    {
        return *ms_pPedestrianGuardClass;
    }
}

namespace AI
{
    bool PedestrianGuard::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPedestrianGuardClass->IsA(c);
    }
}

// CD2 0x82F92DE8: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar PedestrianGuardcPedestrianBaseInheritRegistrar(
        AI::PedestrianGuard::StaticCreateClass(), AI::cPedestrianBase::StaticCreateClass());
}

#include "gom/proto_registrar.h"

// CD2 0x82F92EA0: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar PedestrianGuardSpawningRegistrar(
        PedestrianGuard::StaticCreateClass(), PedestrianGuard::SpawnFromPrototype);
}
