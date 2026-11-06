// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/NPCBehaviour.h"
#include "AI/cPilotRespawn.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *cPilotRespawn::ms_pcPilotRespawnClass = &cPilotRespawn::StaticCreateClass();

    cPilotRespawn::cPilotRespawn() {}

    const Fun_Runtime::cClass &cPilotRespawn::RetClass() const
    {
        return *ms_pcPilotRespawnClass;
    }

    const char *cPilotRespawn::RetClassName() const
    {
        return "cPilotRespawn";
    }

    bool cPilotRespawn::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcPilotRespawnClass->IsA(c);
    }

    RWS::CAttributeHandler *cPilotRespawn::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cPilotRespawn();
    }

    static RWS::CClassFactory::CRegistrar cPilotRespawnRegistrar(
        "cPilotRespawn", cPilotRespawn::MakeNew, 0x130, false);

    Fun_Runtime::cClass &cPilotRespawn::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cPilotRespawnClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "cPilotRespawn", 0x130);
        return *cPilotRespawnClass;
    }

    // CD2 0x82F9C1B8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar cPilotRespawnNPCBehaviourInheritRegistrar(
        AI::cPilotRespawn::StaticCreateClass(), AI::NPCBehaviour::StaticCreateClass());

    // CD2 0x82F9C270: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar cPilotRespawnSpawningRegistrar(
        cPilotRespawn::StaticCreateClass(), cPilotRespawn::SpawnFromPrototype);

    RWS::CAttributeHandler *cPilotRespawn::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) cPilotRespawn;
        return 0;
    }
}
