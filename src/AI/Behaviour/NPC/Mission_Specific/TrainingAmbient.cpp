#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/TrainingAmbient.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *TrainingAmbient::ms_pTrainingAmbientClass = &TrainingAmbient::StaticCreateClass();

    const Fun_Runtime::cClass &TrainingAmbient::RetClass() const
    {
        return *ms_pTrainingAmbientClass;
    }

    const char *TrainingAmbient::RetClassName() const
    {
        return "TrainingAmbient";
    }

    bool TrainingAmbient::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pTrainingAmbientClass->IsA(c);
    }

    RWS::CAttributeHandler *TrainingAmbient::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new TrainingAmbient();
    }
}

static RWS::CClassFactory::CRegistrar TrainingAmbientRegistrar(
    "TrainingAmbient", AI::TrainingAmbient::MakeNew, 0xD0, false);

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &TrainingAmbient::StaticCreateClass()
    {
        static Fun_Runtime::cClass *TrainingAmbientClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "TrainingAmbient", 0xD0);
        return *TrainingAmbientClass;
    }
}

// CD2 0x82F98380: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar TrainingAmbientNPCBehaviourInheritRegistrar(
        AI::TrainingAmbient::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824C7C60: placement factory; NPCBehaviour's constructor (0x824A89C8) stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *TrainingAmbient::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) TrainingAmbient;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F98438: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar TrainingAmbientSpawningRegistrar(
        TrainingAmbient::StaticCreateClass(), TrainingAmbient::SpawnFromPrototype);
}
