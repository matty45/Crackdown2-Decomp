// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "AI/BehaviourClassID.h"
#include "fun_runtime/inheritance_registrar.h"
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

    Fun_Runtime::cClass &CellGuard::StaticCreateClass()
    {
        static Fun_Runtime::cClass *CellGuardClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "CellGuard", 0x1A0);
        return *CellGuardClass;
    }

    const Fun_Runtime::cClass *CellGuard::ms_pCellGuardClass = &CellGuard::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar CellGuardNPCArmedBehaviourInheritRegistrar(
        CellGuard::StaticCreateClass(), NPCArmedBehaviour::StaticCreateClass());

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
        return *ms_pCellGuardClass;
    }
}
