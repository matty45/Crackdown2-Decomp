#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/BeaconDropBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *BeaconDropBehaviour::ms_pBeaconDropBehaviourClass = &BeaconDropBehaviour::StaticCreateClass();


    const Fun_Runtime::cClass &BeaconDropBehaviour::RetClass() const
    {
        return *ms_pBeaconDropBehaviourClass;
    }

    const char *BeaconDropBehaviour::RetClassName() const
    {
        return "BeaconDropBehaviour";
    }

    bool BeaconDropBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pBeaconDropBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *BeaconDropBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new BeaconDropBehaviour();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar BeaconDropBehaviourRegistrar(
        "BeaconDropBehaviour", BeaconDropBehaviour::MakeNew, 0x150, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &BeaconDropBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *BeaconDropBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "BeaconDropBehaviour", 0x150);
        return *BeaconDropBehaviourClass;
    }
}

// CD2 0x82F97F48: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar BeaconDropBehaviourcPilotBaseInheritRegistrar(
        AI::BeaconDropBehaviour::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());
}

#include <new>

// CD2 0x824C77C8: placement factory; cPilotBase's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *BeaconDropBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) BeaconDropBehaviour;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F98000: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar BeaconDropBehaviourSpawningRegistrar(
        BeaconDropBehaviour::StaticCreateClass(), BeaconDropBehaviour::SpawnFromPrototype);
}
