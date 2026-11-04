#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/cPilotBase.h"
#include "AI/cAgentPickup.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *cAgentPickup::ms_pcAgentPickupClass = &cAgentPickup::StaticCreateClass();

    cAgentPickup::cAgentPickup() {}

    const Fun_Runtime::cClass &cAgentPickup::RetClass() const
    {
        return *ms_pcAgentPickupClass;
    }

    const char *cAgentPickup::RetClassName() const
    {
        return "cAgentPickup";
    }

    bool cAgentPickup::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcAgentPickupClass->IsA(c);
    }

    RWS::CAttributeHandler *cAgentPickup::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cAgentPickup();
    }
}

namespace AI
{
    static RWS::CClassFactory::CRegistrar cAgentPickupRegistrar(
        "cAgentPickup", cAgentPickup::MakeNew, 0x140, false);
}

#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    Fun_Runtime::cClass &cAgentPickup::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cAgentPickupClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cAgentPickup", 0x140);
        return *cAgentPickupClass;
    }
}

// CD2 0x82F9A978: runtime class inheritance registration.
namespace AI
{
    static Fun_Runtime::cInheritanceRegistrar cAgentPickupcPilotBaseInheritRegistrar(
        AI::cAgentPickup::StaticCreateClass(), AI::cPilotBase::StaticCreateClass());
}

// CD2 0x82F9AA30: register the class descriptor and placement factory.
namespace AI
{
    static GOM::cProtoRegistrar cAgentPickupSpawningRegistrar(
        cAgentPickup::StaticCreateClass(), cAgentPickup::SpawnFromPrototype);
}
