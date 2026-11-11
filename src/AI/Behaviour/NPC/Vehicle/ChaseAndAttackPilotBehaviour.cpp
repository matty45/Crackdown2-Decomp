// AI/Behaviour/NPC/Vehicle/ChaseAndAttackPilotBehaviour.cpp: RuffKing's Libraries/Shared/AI/Behaviour/NPC/Vehicle/ChaseAndAttackPilotBehaviour.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "AI/aiconstants.h"
#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "gom/proto_registrar.h"
#include "rws/classfactory.h"
#include "AI/cChaseAndAttackPilotBehaviour.h"
#include "cd2/memory.h"

namespace AI
{
    const Fun_Runtime::cClass *cChaseAndAttackPilotBehaviour::ms_pcChaseAndAttackPilotBehaviourClass = &cChaseAndAttackPilotBehaviour::StaticCreateClass();

    const char *cChaseAndAttackPilotBehaviour::RetClassName() const
    {
        return "cChaseAndAttackPilotBehaviour";
    }

    static Fun_Runtime::cInheritanceRegistrar cChaseAndAttackPilotBehaviourcAgressiveResponsePilotBehaviourInheritRegistrar(
        cChaseAndAttackPilotBehaviour::StaticCreateClass(), cAgressiveResponsePilotBehaviour::StaticCreateClass());

    static RWS::CClassFactory::CRegistrar cChaseAndAttackPilotBehaviourRegistrar(
        "cChaseAndAttackPilotBehaviour", cChaseAndAttackPilotBehaviour::MakeNew, 0x170, false);

    static GOM::cProtoRegistrar cChaseAndAttackPilotBehaviourSpawningRegistrar(
        cChaseAndAttackPilotBehaviour::StaticCreateClass(), cChaseAndAttackPilotBehaviour::SpawnFromPrototype);
}
