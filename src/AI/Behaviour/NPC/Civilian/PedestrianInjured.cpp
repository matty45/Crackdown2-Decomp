#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/PedestrianGuard.h"
#include "AI/PedestrianInjured.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include <new>

namespace AI
{
    const Fun_Runtime::cClass *PedestrianInjured::ms_pPedestrianInjuredClass = &PedestrianInjured::StaticCreateClass();

    RWS::CAttributeHandler *PedestrianInjured::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) PedestrianInjured;
        return 0;
    }

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

    static RWS::CClassFactory::CRegistrar PedestrianInjuredRegistrar(
        "PedestrianInjured", PedestrianInjured::MakeNew, 0x130, false);

    Fun_Runtime::cClass &PedestrianInjured::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianInjuredClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "PedestrianInjured", 0x130);
        return *PedestrianInjuredClass;
    }

    // CD2 0x82F93230: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar PedestrianInjuredPedestrianGuardInheritRegistrar(
        AI::PedestrianInjured::StaticCreateClass(), AI::PedestrianGuard::StaticCreateClass());

    // CD2 0x82F932E8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar PedestrianInjuredSpawningRegistrar(
        PedestrianInjured::StaticCreateClass(), PedestrianInjured::SpawnFromPrototype);
}
