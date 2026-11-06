// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/FreakBase.h"
#include "AI/Scrounger.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    RWS::CAttributeHandler *Scrounger::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new ScroungerPrototype(packet);
    }

    const char *Scrounger::RetClassName() const
    {
        return "Scrounger";
    }

    static RWS::CClassFactory::CRegistrar ScroungerRegistrar(
        "Scrounger", Scrounger::MakeNew, 0x130, false);

    Fun_Runtime::cClass &Scrounger::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ScroungerClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Scrounger", 0x130);
        return *ScroungerClass;
    }

    const Fun_Runtime::cClass *Scrounger::ms_pScroungerClass = &Scrounger::StaticCreateClass();

    const Fun_Runtime::cClass &Scrounger::RetClass() const
    {
        return *ms_pScroungerClass;
    }

    bool Scrounger::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pScroungerClass->IsA(c);
    }

    // CD2 0x82F94310: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar ScroungerFreakBaseInheritRegistrar(
        AI::Scrounger::StaticCreateClass(), AI::FreakBase::StaticCreateClass());

    // CD2 0x82F943C8: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar ScroungerSpawningRegistrar(
        Scrounger::StaticCreateClass(), Scrounger::SpawnFromPrototype);

    RWS::CAttributeHandler *Scrounger::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) Scrounger;
        return 0;
    }
}
