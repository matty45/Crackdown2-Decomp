#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/cVehicleCollectionBehaviour.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cVehicleCollectionBehaviour::ms_pcVehicleCollectionBehaviourClass = &cVehicleCollectionBehaviour::StaticCreateClass();

    cVehicleCollectionBehaviour::cVehicleCollectionBehaviour() {}

    const Fun_Runtime::cClass &cVehicleCollectionBehaviour::RetClass() const
    {
        return *ms_pcVehicleCollectionBehaviourClass;
    }

    const char *cVehicleCollectionBehaviour::RetClassName() const
    {
        return "cVehicleCollectionBehaviour";
    }

    bool cVehicleCollectionBehaviour::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcVehicleCollectionBehaviourClass->IsA(c);
    }

    RWS::CAttributeHandler *cVehicleCollectionBehaviour::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleCollectionBehaviour();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cVehicleCollectionBehaviourRegistrar(
        "cVehicleCollectionBehaviour", cVehicleCollectionBehaviour::MakeNew, 0x160, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cVehicleCollectionBehaviour::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cVehicleCollectionBehaviourClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cVehicleCollectionBehaviour", 0x160);
        return *cVehicleCollectionBehaviourClass;
    }
}

// CD2 0x82F9CE60: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cVehicleCollectionBehaviourcPilotBaseInheritRegistrar(
        AI::cVehicleCollectionBehaviour::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());
}

// CD2 0x82F9CF18: register the class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cVehicleCollectionBehaviourSpawningRegistrar(
        cVehicleCollectionBehaviour::StaticCreateClass(), cVehicleCollectionBehaviour::SpawnFromPrototype);
}
