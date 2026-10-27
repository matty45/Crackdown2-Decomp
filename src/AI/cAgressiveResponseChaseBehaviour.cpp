#include "AI/cAgressiveResponseChaseBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgressiveResponseChaseBehaviour::ms_pcAgressiveResponseChaseBehaviourClass = 0;

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

static RWS::CClassFactory::CRegistrar cAgressiveResponseChaseBehaviourRegistrar(
    "cAgressiveResponseChaseBehaviour", AI::cAgressiveResponseChaseBehaviour::MakeNew, 0x7C, false);
