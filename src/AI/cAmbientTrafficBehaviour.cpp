#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cAmbientTrafficBehaviour.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

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

    static RWS::CClassFactory::CRegistrar cAmbientTrafficBehaviourRegistrar(
        "cAmbientTrafficBehaviour", cAmbientTrafficBehaviour::MakeNew, 0x140, false);

    Fun_Runtime::cClass &cAmbientTrafficBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAmbientTrafficBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAmbientTrafficBehaviour", 0x140);
        return *cAmbientTrafficBehaviourClass;
    }

    // CD2 0x82F99898: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cAmbientTrafficBehaviourNPCBehaviourInheritRegistrar(
        AI::cAmbientTrafficBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F99950: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cAmbientTrafficBehaviourSpawningRegistrar(
        cAmbientTrafficBehaviour::StaticCreateClass(), cAmbientTrafficBehaviour::SpawnFromPrototype);

    RWS::CAttributeHandler *cAmbientTrafficBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cAmbientTrafficBehaviour;
        return 0;
    }
}
