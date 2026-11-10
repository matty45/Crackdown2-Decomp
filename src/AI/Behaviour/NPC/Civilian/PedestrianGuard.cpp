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
#include "AI/cPedestrianBase.h"
#include "AI/PedestrianGuard.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    // CD2 0x824AB020: the class factory builds the prototype.
    RWS::CAttributeHandler *PedestrianGuard::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new PedestrianGuardPrototype(packet);
    }

    const char *PedestrianGuard::RetClassName() const
    {
        return "PedestrianGuard";
    }

    static RWS::CClassFactory::CRegistrar PedestrianGuardRegistrar(
        "PedestrianGuard", PedestrianGuard::MakeNew, 0x130, false);

    Fun_Runtime::cClass &PedestrianGuard::StaticCreateClass()
    {
        static Fun_Runtime::cClass *PedestrianGuardClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "PedestrianGuard", 0x130);
        return *PedestrianGuardClass;
    }

    const Fun_Runtime::cClass *PedestrianGuard::ms_pPedestrianGuardClass = &PedestrianGuard::StaticCreateClass();

    const Fun_Runtime::cClass &PedestrianGuard::RetClass() const
    {
        return *ms_pPedestrianGuardClass;
    }

    bool PedestrianGuard::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pPedestrianGuardClass->IsA(c);
    }

    PedestrianGuard::PedestrianGuard() : m_nUnknown120(0), m_nUnknown124(0) {}

    // CD2 0x82F92DE8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar PedestrianGuardcPedestrianBaseInheritRegistrar(
        AI::PedestrianGuard::StaticCreateClass(), AI::cPedestrianBase::StaticCreateClass());

    // CD2 0x82F92EA0: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar PedestrianGuardSpawningRegistrar(
        PedestrianGuard::StaticCreateClass(), PedestrianGuard::SpawnFromPrototype);

    RWS::CAttributeHandler *PedestrianGuard::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) PedestrianGuard;
        return 0;
    }
}
