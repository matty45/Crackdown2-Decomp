#include "fun_runtime/inheritance_registrar.h"
#include "AI/cAmbientTrafficBehaviour.h"
#include "AI/cAmbientWanderAttackBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const char *cAmbientWanderAttackBehaviour::RetClassName() const
    {
        return "cAmbientWanderAttackBehaviour";
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAmbientWanderAttackBehaviourRegistrar(
        "cAmbientWanderAttackBehaviour", cAmbientWanderAttackBehaviour::MakeNew, 0x150, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cAmbientWanderAttackBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientWanderAttackBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAmbientWanderAttackBehaviour", 0x150);
        return *cAmbientWanderAttackBehaviourClass;
    }
}

namespace AI
{
    const Fun_Runtime::cClass *cAmbientWanderAttackBehaviour::ms_pcAmbientWanderAttackBehaviourClass = &cAmbientWanderAttackBehaviour::StaticCreateClass();

    const Fun_Runtime::cClass &cAmbientWanderAttackBehaviour::RetClass() const
    {
        return *ms_pcAmbientWanderAttackBehaviourClass;
    }
}

namespace AI
{
    bool cAmbientWanderAttackBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAmbientWanderAttackBehaviourClass->IsA(c);
    }
}

// CD2 0x82F99CD0: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cAmbientWanderAttackBehaviourcAmbientTrafficBehaviourInheritRegistrar(
        AI::cAmbientWanderAttackBehaviour::StaticCreateClass(), AI::cAmbientTrafficBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824CDD78: placement factory; the constructor stays out of line (a tail call).
namespace AI
{
    RWS::CAttributeHandler *cAmbientWanderAttackBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAmbientWanderAttackBehaviour;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F99D88: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cAmbientWanderAttackBehaviourSpawningRegistrar(
        cAmbientWanderAttackBehaviour::StaticCreateClass(), cAmbientWanderAttackBehaviour::SpawnFromPrototype);
}
