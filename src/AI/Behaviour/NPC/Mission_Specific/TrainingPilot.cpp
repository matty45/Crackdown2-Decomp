#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/TrainingPilot.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingPilot::ms_pTrainingPilotClass = &TrainingPilot::StaticCreateClass();


    const Fun_Runtime::cClass &TrainingPilot::RetClass() const
    {
        return *ms_pTrainingPilotClass;
    }

    const char *TrainingPilot::RetClassName() const
    {
        return "TrainingPilot";
    }

    bool TrainingPilot::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingPilotClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingPilot::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingPilot();
    }
}

static RWS::CClassFactory::CRegistrar TrainingPilotRegistrar(
    "TrainingPilot", AI::TrainingPilot::MakeNew, 0xD0, false);

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &TrainingPilot::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingPilotClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingPilot", 0xD0);
        return *TrainingPilotClass;
    }
}

// CD2 0x82F98BF0: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar TrainingPilotNPCBehaviourInheritRegistrar(
        AI::TrainingPilot::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824C8DA8: placement factory; NPCBehaviour's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *TrainingPilot::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) TrainingPilot;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F98CA8: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar TrainingPilotSpawningRegistrar(
        TrainingPilot::StaticCreateClass(), TrainingPilot::SpawnFromPrototype);
}
