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

    RWS::CAttributeHandler *cAgressiveResponseChaseBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgressiveResponseChaseBehaviour();
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
