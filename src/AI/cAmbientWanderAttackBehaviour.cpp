#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cAmbientTrafficBehaviour.h"
#include "AI/cAmbientWanderAttackBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const char *cAmbientWanderAttackBehaviour::RetClassName() const
    {
        return "cAmbientWanderAttackBehaviour";
    }

    static RWS::CClassFactory::CRegistrar cAmbientWanderAttackBehaviourRegistrar(
        "cAmbientWanderAttackBehaviour", cAmbientWanderAttackBehaviour::MakeNew, 0x150, false);

    Fun_Runtime::cClass &cAmbientWanderAttackBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientWanderAttackBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAmbientWanderAttackBehaviour", 0x150);
        return *cAmbientWanderAttackBehaviourClass;
    }

    const Fun_Runtime::cClass *cAmbientWanderAttackBehaviour::ms_pcAmbientWanderAttackBehaviourClass = &cAmbientWanderAttackBehaviour::StaticCreateClass();

    const Fun_Runtime::cClass &cAmbientWanderAttackBehaviour::RetClass() const
    {
        return *ms_pcAmbientWanderAttackBehaviourClass;
    }

    bool cAmbientWanderAttackBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAmbientWanderAttackBehaviourClass->IsA(c);
    }

    // CD2 0x82F99CD0: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAmbientWanderAttackBehaviourcAmbientTrafficBehaviourInheritRegistrar(
        AI::cAmbientWanderAttackBehaviour::StaticCreateClass(), AI::cAmbientTrafficBehaviour::StaticCreateClass());

    // CD2 0x82F99D88: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAmbientWanderAttackBehaviourSpawningRegistrar(
        cAmbientWanderAttackBehaviour::StaticCreateClass(), cAmbientWanderAttackBehaviour::SpawnFromPrototype);

    RWS::CAttributeHandler *cAmbientWanderAttackBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAmbientWanderAttackBehaviour;
        return 0;
    }
}
