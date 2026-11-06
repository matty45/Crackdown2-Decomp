#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "cd2/memory.h"
#include "gom/proto_registrar.h"
#include "AI/CellGuard.h"
#include "AI/CellGuardPrototype.h"
#include "rws/classfactory.h"

namespace AI
{
    RWS::CAttributeHandler *CellGuard::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new CellGuardPrototype(packet);
    }

    const char *CellGuard::RetClassName() const
    {
        return "CellGuard";
    }

    static RWS::CClassFactory::CRegistrar CellGuardRegistrar(
        "CellGuard", CellGuard::MakeNew, 0x1A0, false);

    // CD2 0x82F95B88: class descriptor and placement factory.
    static GOM::cProtoRegistrar CellGuardSpawningRegistrar(
        CellGuard::StaticCreateClass(), CellGuard::SpawnFromPrototype);

    RWS::CAttributeHandler *CellGuard::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) CellGuard;
        return 0;
    }

    const Fun_Runtime::cClass &CellGuard::RetClass() const
    {
        return *ms_pcCellGuardClass;
    }
}
