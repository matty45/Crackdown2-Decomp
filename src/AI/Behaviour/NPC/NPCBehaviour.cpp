#include "AI/NPCBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *NPCBehaviour::ms_pNPCBehaviourClass = 0;

    NPCBehaviour::NPCBehaviour() {}

    const Fun_Runtime::cClass &NPCBehaviour::RetClass() const
    {
        return *ms_pNPCBehaviourClass;
    }

    const char *NPCBehaviour::RetClassName() const
    {
        return "NPCBehaviour";
    }

    bool NPCBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pNPCBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *NPCBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new NPCBehaviour();
    }
}

static RWS::CClassFactory::CRegistrar NPCBehaviourRegistrar(
    "NPCBehaviour", AI::NPCBehaviour::MakeNew, 0x7C, false);

namespace AI
{
    static RWS::CClassFactory::CRegistrar NPCBehaviourRegistrar(
        "NPCBehaviour", NPCBehaviour::MakeNew, 0xC0, false);
}
