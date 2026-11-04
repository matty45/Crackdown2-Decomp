#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPedestrianBase.h"
#include "AI/Pedestrian.h"
#include "rws/classfactory.h"
#include "gom/proto_registrar.h"

#include <new>

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
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar PedestrianRegistrar(
        "Pedestrian", Pedestrian::MakeNew, 0x120, false);
    static GOM::cProtoRegistrar PedestrianSpawningRegistrar(
        Pedestrian::StaticCreateClass(), Pedestrian::SpawnFromPrototype);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &Pedestrian::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Pedestrian", 0x120);
        return *PedestrianClass;
    }
}

// CD2 0x82F92578: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar PedestriancPedestrianBaseInheritRegistrar(
        AI::Pedestrian::StaticCreateClass(), AI::cPedestrianBase::StaticCreateClass());
}
