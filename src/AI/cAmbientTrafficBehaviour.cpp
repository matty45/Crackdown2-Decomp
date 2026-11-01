#include "AI/cAmbientTrafficBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAmbientTrafficBehaviour::ms_pcAmbientTrafficBehaviourClass = &cAmbientTrafficBehaviour::StaticCreateClass();

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

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAmbientTrafficBehaviourRegistrar(
        "cAmbientTrafficBehaviour", cAmbientTrafficBehaviour::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cAmbientTrafficBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientTrafficBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAmbientTrafficBehaviour", 0x140);
        return *cAmbientTrafficBehaviourClass;
    }
}
