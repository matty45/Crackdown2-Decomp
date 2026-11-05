#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPedestrianBase.h"
#include "AI/PedestrianGuard.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const char *PedestrianGuard::RetClassName() const
    {
        return "PedestrianGuard";
    }

    static RWS::CClassFactory::CRegistrar PedestrianGuardRegistrar(
        "PedestrianGuard", PedestrianGuard::MakeNew, 0x130, false);

    Fun_Runtime::cClass &PedestrianGuard::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianGuardClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "PedestrianGuard", 0x130);
        return *PedestrianGuardClass;
    }

    const Fun_Runtime::cClass *PedestrianGuard::ms_pPedestrianGuardClass = &PedestrianGuard::StaticCreateClass();

    const Fun_Runtime::cClass &PedestrianGuard::RetClass() const
    {
        return *ms_pPedestrianGuardClass;
    }

    bool PedestrianGuard::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPedestrianGuardClass->IsA(c);
    }

    // CD2 0x82F92DE8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar PedestrianGuardcPedestrianBaseInheritRegistrar(
        AI::PedestrianGuard::StaticCreateClass(), AI::cPedestrianBase::StaticCreateClass());

    // CD2 0x82F92EA0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar PedestrianGuardSpawningRegistrar(
        PedestrianGuard::StaticCreateClass(), PedestrianGuard::SpawnFromPrototype);

    RWS::CAttributeHandler *PedestrianGuard::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) PedestrianGuard;
        return 0;
    }
}
