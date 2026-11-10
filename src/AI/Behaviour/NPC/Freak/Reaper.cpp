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
#include "AI/FreakBase.h"
#include "AI/Reaper.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"

namespace AI
{
    const Fun_Runtime::cClass *Reaper::ms_pReaperClass = &Reaper::StaticCreateClass();

    Reaper::Reaper() {}

    const Fun_Runtime::cClass &Reaper::RetClass() const
    {
        return *ms_pReaperClass;
    }

    RWS::CAttributeHandler *Reaper::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new ReaperPrototype(packet);
    }

    const char *Reaper::RetClassName() const
    {
        return "Reaper";
    }

    // CD2 0x824B26A8: placement factory; the constructor stays out of line (a tail call).
    RWS::CAttributeHandler *Reaper::SpawnFromPrototype(GOM::cObjectPrototype *prototype, void *memory)
    {
        if (memory)
            return new (memory) Reaper(prototype);
        return 0;
    }

    bool Reaper::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pReaperClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar ReaperRegistrar(
        "Reaper", Reaper::MakeNew, 0x220, false);

    Fun_Runtime::cClass &Reaper::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ReaperClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "Reaper", 0x220);
        return *ReaperClass;
    }

    // CD2 0x82F93ED8: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar ReaperFreakBaseInheritRegistrar(
        AI::Reaper::StaticCreateClass(), AI::FreakBase::StaticCreateClass());

    // CD2 0x82F93F90: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar ReaperSpawningRegistrar(
        Reaper::StaticCreateClass(), Reaper::SpawnFromPrototype);
}
