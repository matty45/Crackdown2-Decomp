#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cPilotBase.h"
#include "rws/classfactory.h"

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
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cPilotBaseRegistrar(
        "cPilotBase", cPilotBase::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cPilotBase::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPilotBaseClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cPilotBase", 0x140);
        return *cPilotBaseClass;
    }
}

// CD2 0x82F9BD80: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cPilotBaseNPCBehaviourInheritRegistrar(
        AI::cPilotBase::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824D31B0: placement factory; the constructor stays out of line (a tail call).
namespace AI
{
    RWS::CAttributeHandler *cPilotBase::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPilotBase;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F9BE38: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cPilotBaseSpawningRegistrar(
        cPilotBase::StaticCreateClass(), cPilotBase::SpawnFromPrototype);
}
