// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "rws/classfactory.h"
#include "VFX/cLinkedVFXPrototype.h"
#include "VFX/cLinkedVFXSpawner.h"
#include "cd2/memory.h"

namespace VFX
{
    RWS::CAttributeHandler *cLinkedVFXPrototype::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cLinkedVFXPrototype(packet);
    }

    const char *cLinkedVFXPrototype::RetClassName() const
    {
        return "cLinkedVFXPrototype";
    }

    // CD2 keeps these spawner interface bodies in this file's range. The table
    // installed by the spawner factory at 0x827FA780 identifies their owner.
    const Fun_Runtime::cClass &cLinkedVFXSpawner::RetClass() const
    {
        return *ms_pcLinkedVFXSpawnerClass;
    }

    void cLinkedVFXPrototype::HandleAttributes(const RWS::CAttributePacket &packet)
    {
        cAmbientVFXPrototypeBase::HandleAttributes(packet);
        if (packet.IsInstanceCreationPacket())
            m_EventHandler.Register(this, packet.GetInstanceId());
    }

    static RWS::CClassFactory::CRegistrar cLinkedVFXPrototypeRegistrar(
        "cLinkedVFXPrototype", cLinkedVFXPrototype::MakeNew, 0x44, false);
}
