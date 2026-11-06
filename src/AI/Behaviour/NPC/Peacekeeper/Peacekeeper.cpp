// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "AI/Peacekeeper.h"
#include "rws/classfactory.h"

namespace AI
{
    const Fun_Runtime::cClass *Peacekeeper::ms_pPeacekeeperClass = 0;

    Peacekeeper::Peacekeeper() {}

    const Fun_Runtime::cClass &Peacekeeper::RetClass() const
    {
        return *ms_pPeacekeeperClass;
    }

    const char *Peacekeeper::RetClassName() const
    {
        return "Peacekeeper";
    }

    bool Peacekeeper::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPeacekeeperClass->IsA(c);
    }

    RWS::CAttributeHandler *Peacekeeper::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new Peacekeeper();
    }

    static RWS::CClassFactory::CRegistrar PeacekeeperRegistrar(
        "Peacekeeper", Peacekeeper::MakeNew, 0x1E0, false);

    // CD2 0x82F978A8: class descriptor and placement factory.
    static GOM::cProtoRegistrar PeacekeeperSpawningRegistrar(
        Peacekeeper::StaticCreateClass(), Peacekeeper::SpawnFromPrototype);

    RWS::CAttributeHandler *Peacekeeper::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) Peacekeeper;
        return 0;
    }
}
