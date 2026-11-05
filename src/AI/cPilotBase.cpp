#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cPilotBase.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *cPilotBase::ms_pcPilotBaseClass = &cPilotBase::StaticCreateClass();

    cPilotBase::cPilotBase() {}

    const Fun_Runtime::cClass &cPilotBase::RetClass() const
    {
        return *ms_pcPilotBaseClass;
    }

    const char *cPilotBase::RetClassName() const
    {
        return "cPilotBase";
    }

    bool cPilotBase::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPilotBaseClass->IsA(c);
    }

    RWS::CAttributeHandler *cPilotBase::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPilotBase();
    }

    static RWS::CClassFactory::CRegistrar cPilotBaseRegistrar(
        "cPilotBase", cPilotBase::MakeNew, 0x140, false);

    Fun_Runtime::cClass &cPilotBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPilotBaseClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cPilotBase", 0x140);
        return *cPilotBaseClass;
    }

    // CD2 0x82F9BD80: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPilotBaseNPCBehaviourInheritRegistrar(
        AI::cPilotBase::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F9BE38: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPilotBaseSpawningRegistrar(
        cPilotBase::StaticCreateClass(), cPilotBase::SpawnFromPrototype);

    RWS::CAttributeHandler *cPilotBase::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPilotBase;
        return 0;
    }
}
