#include "AI/cAmbientTrafficBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAmbientTrafficBehaviour::ms_pcAmbientTrafficBehaviourClass = 0;

    cAmbientTrafficBehaviour::cAmbientTrafficBehaviour() {}

    const Fun_Runtime::cClass &cAmbientTrafficBehaviour::RetClass() const
    {
        return *ms_pcAmbientTrafficBehaviourClass;
    }

    const char *cAmbientTrafficBehaviour::RetClassName() const
    {
        return "cAmbientTrafficBehaviour";
    }

    bool cAmbientTrafficBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAmbientTrafficBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *cAmbientTrafficBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAmbientTrafficBehaviour();
    }
}

static RWS::CClassFactory::CRegistrar cAmbientTrafficBehaviourRegistrar(
    "cAmbientTrafficBehaviour", AI::cAmbientTrafficBehaviour::MakeNew, 0x7C, false);
