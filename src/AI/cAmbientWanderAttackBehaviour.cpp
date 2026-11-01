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
