#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cVehicleAttackedRockingBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cVehicleAttackedRockingBehaviour::ms_pcVehicleAttackedRockingBehaviourClass = &cVehicleAttackedRockingBehaviour::StaticCreateClass();


    const Fun_Runtime::cClass &cVehicleAttackedRockingBehaviour::RetClass() const
    {
        return *ms_pcVehicleAttackedRockingBehaviourClass;
    }

    const char *cVehicleAttackedRockingBehaviour::RetClassName() const
    {
        return "cVehicleAttackedRockingBehaviour";
    }

    bool cVehicleAttackedRockingBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVehicleAttackedRockingBehaviourClass->IsA(c);
    }

}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cVehicleAttackedRockingBehaviourRegistrar(
        "cVehicleAttackedRockingBehaviour", cVehicleAttackedRockingBehaviour::MakeNew, 0xD0, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cVehicleAttackedRockingBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVehicleAttackedRockingBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cVehicleAttackedRockingBehaviour", 0xD0);
        return *cVehicleAttackedRockingBehaviourClass;
    }
}

// CD2 0x82F9A540: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cVehicleAttackedRockingBehaviourNPCBehaviourInheritRegistrar(
        AI::cVehicleAttackedRockingBehaviour::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());
}

#include <new>

// CD2 0x824CF790: placement factory; NPCBehaviour's constructor stays out of line, the rest is inlined.
namespace AI
{
    RWS::CAttributeHandler *cVehicleAttackedRockingBehaviour::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cVehicleAttackedRockingBehaviour;
        return 0;
    }
}

#include "gom/proto_registrar.h"

// CD2 0x82F9A5F8: the spawning registrar (GOM::cProtoRegistrar constructor 0x82657690) pairs the runtime class with
// its placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cVehicleAttackedRockingBehaviourSpawningRegistrar(
        cVehicleAttackedRockingBehaviour::StaticCreateClass(), cVehicleAttackedRockingBehaviour::SpawnFromPrototype);
}

// CD2 0x824CF6C8: the class factory builds the prototype.
namespace AI
{
    RWS::CAttributeHandler *cVehicleAttackedRockingBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleAttackedRockingBehaviourPrototype(packet);
    }
}
