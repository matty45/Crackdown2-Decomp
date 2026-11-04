#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/cTrainingHeliPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cTrainingHeliPilot::ms_pcTrainingHeliPilotClass = &cTrainingHeliPilot::StaticCreateClass();


    const Fun_Runtime::cClass &cTrainingHeliPilot::RetClass() const
    {
        return *ms_pcTrainingHeliPilotClass;
    }

    const char *cTrainingHeliPilot::RetClassName() const
    {
        return "cTrainingHeliPilot";
    }

    bool cTrainingHeliPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcTrainingHeliPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *cTrainingHeliPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cTrainingHeliPilot();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cTrainingHeliPilotRegistrar(
        "cTrainingHeliPilot", cTrainingHeliPilot::MakeNew, 0x150, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cTrainingHeliPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cTrainingHeliPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cTrainingHeliPilot", 0x150);
        return *cTrainingHeliPilotClass;
    }
}

// CD2 0x82F9CA28: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cTrainingHeliPilotcPilotBaseInheritRegistrar(
        AI::cTrainingHeliPilot::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());
}

#include <new>

// CD2 0x824D5350: placement factory; cPilotBase's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *cTrainingHeliPilot::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cTrainingHeliPilot;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F9CAE0: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cTrainingHeliPilotSpawningRegistrar(
        cTrainingHeliPilot::StaticCreateClass(), cTrainingHeliPilot::SpawnFromPrototype);
}
