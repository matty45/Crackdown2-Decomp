#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/TrainingDummy.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "gom/game_base.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingDummy::ms_pTrainingDummyClass = &TrainingDummy::StaticCreateClass();

    RWS::CAttributeHandler *TrainingDummy::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) TrainingDummy;
        return 0;
    }

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

    static RWS::CClassFactory::CRegistrar TrainingDummyRegistrar(
        "TrainingDummy", TrainingDummy::MakeNew, 0xD0, false);
}

// cGameBase's setter is folded into this split; TrainingDummy itself is only 0xD0 bytes.
void cGameBase::SetFullHealth(float health)
{
    m_fFullHealth = health;
}

namespace AI
{
    Fun_Runtime::cClass &TrainingDummy::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingDummyClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingDummy", 0xD0);
        return *TrainingDummyClass;
    }

    // CD2 0x82F987B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar TrainingDummyNPCBehaviourInheritRegistrar(
        AI::TrainingDummy::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F98870: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar TrainingDummySpawningRegistrar(
        TrainingDummy::StaticCreateClass(), TrainingDummy::SpawnFromPrototype);
}
