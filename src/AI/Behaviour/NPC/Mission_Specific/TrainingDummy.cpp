#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/TrainingDummy.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingDummy::ms_pTrainingDummyClass = &TrainingDummy::StaticCreateClass();


    const Fun_Runtime::cClass &TrainingDummy::RetClass() const
    {
        return *ms_pTrainingDummyClass;
    }

    const char *TrainingDummy::RetClassName() const
    {
        return "TrainingDummy";
    }

    bool TrainingDummy::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingDummyClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingDummy::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingDummy();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar TrainingDummyRegistrar(
        "TrainingDummy", TrainingDummy::MakeNew, 0xD0, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &TrainingDummy::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingDummyClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingDummy", 0xD0);
        return *TrainingDummyClass;
    }
}

// CD2 0x82F987B8: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar TrainingDummyNPCBehaviourInheritRegistrar(
        AI::TrainingDummy::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824C82D8: placement factory; NPCBehaviour's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *TrainingDummy::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) TrainingDummy;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F98870: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar TrainingDummySpawningRegistrar(
        TrainingDummy::StaticCreateClass(), TrainingDummy::SpawnFromPrototype);
}
