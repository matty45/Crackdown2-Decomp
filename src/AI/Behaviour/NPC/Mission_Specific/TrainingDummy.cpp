#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/TrainingDummy.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingDummy::ms_pTrainingDummyClass = &TrainingDummy::StaticCreateClass();

    TrainingDummy::TrainingDummy() {}

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

// CD2 0x82F98870: register the class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar TrainingDummySpawningRegistrar(
        TrainingDummy::StaticCreateClass(), TrainingDummy::SpawnFromPrototype);
}
