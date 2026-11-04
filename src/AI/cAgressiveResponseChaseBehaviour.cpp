#include "fun_runtime/inheritance_registrar.h"
#include "AI/cAgressiveResponseBase.h"
#include "AI/cAgressiveResponseChaseBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgressiveResponseChaseBehaviour::ms_pcAgressiveResponseChaseBehaviourClass = &cAgressiveResponseChaseBehaviour::StaticCreateClass();

    cAgressiveResponseChaseBehaviour::cAgressiveResponseChaseBehaviour() {}

    const Fun_Runtime::cClass &cAgressiveResponseChaseBehaviour::RetClass() const
    {
        return *ms_pcAgressiveResponseChaseBehaviourClass;
    }

    const char *cAgressiveResponseChaseBehaviour::RetClassName() const
    {
        return "cAgressiveResponseChaseBehaviour";
    }

    bool cAgressiveResponseChaseBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgressiveResponseChaseBehaviourClass->IsA(c);
    }

}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAgressiveResponseChaseBehaviourRegistrar(
        "cAgressiveResponseChaseBehaviour", cAgressiveResponseChaseBehaviour::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cAgressiveResponseChaseBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgressiveResponseChaseBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAgressiveResponseChaseBehaviour", 0x140);
        return *cAgressiveResponseChaseBehaviourClass;
    }
}

// CD2 0x82F99460: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cAgressiveResponseChaseBehaviourcAgressiveResponseBaseInheritRegistrar(
        AI::cAgressiveResponseChaseBehaviour::StaticCreateClass(), AI::cAgressiveResponseBase::StaticCreateClass());
}

// CD2 0x824C9210: the class factory builds the prototype.
namespace AI
{
    RWS::CAttributeHandler *cAgressiveResponseChaseBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgressiveResponseChaseBehaviourPrototype(packet);
    }
}
