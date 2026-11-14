// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/cMissionActivationCylinder.h"
#include "rws/classfactory.h"

namespace AI
{
    static const char *const pcMissionActivationCylinderClassID = "cMissionActivationCylinder";

    RWS::CAttributeHandler *cMissionActivationCylinder::MakeNew(const RWS::CAttributePacket &, bool)
    {
        return new cMissionActivationCylinder;
    }

    const char *cMissionActivationCylinder::RetClassName() const
    {
        return "cMissionActivationCylinder";
    }

    // CD2 0x8248B058: only the member's and the bases' destruction.
    cMissionActivationCylinder::~cMissionActivationCylinder()
    {
    }

    // RuffKing's body (0x823ED4A0) also builds the command iterator and does not read it.
    void cMissionActivationCylinder::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cPlayerTriggerCylinder::HandleAttributes(packet);
        RWS::CAttributeCommandIterator it(packet, pcMissionActivationCylinderClassID);
        if (packet.IsInstanceCreationPacket())
            m_EventHandler.Register(this, packet.GetInstanceId());
    }

    static RWS::CClassFactory::CRegistrar cMissionActivationCylinderRegistrar(
        "cMissionActivationCylinder", cMissionActivationCylinder::MakeNew, 0x110, false);
}
