#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPedestrianBase.h"
#include "AI/Pedestrian.h"
#include "rws/classfactory.h"
#include <new>
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *Pedestrian::ms_pcPedestrianClass = &Pedestrian::StaticCreateClass();

    RWS::CAttributeHandler *Pedestrian::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) Pedestrian;
        return 0;
    }

    const Fun_Runtime::cClass &Pedestrian::RetClass() const
    {
        return *ms_pcPedestrianClass;
    }

    bool Pedestrian::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPedestrianClass->IsA(c);
    }

    const char *Pedestrian::RetClassName() const
    {
        return "Pedestrian";
    }

    static RWS::CClassFactory::CRegistrar PedestrianRegistrar(
        "Pedestrian", Pedestrian::MakeNew, 0x120, false);

    Fun_Runtime::cClass &Pedestrian::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Pedestrian", 0x120);
        return *PedestrianClass;
    }

    // CD2 0x82F92578: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar PedestriancPedestrianBaseInheritRegistrar(
        AI::Pedestrian::StaticCreateClass(), AI::cPedestrianBase::StaticCreateClass());

    // CD2 0x82F92630: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar PedestrianSpawningRegistrar(
        Pedestrian::StaticCreateClass(), Pedestrian::SpawnFromPrototype);
}
