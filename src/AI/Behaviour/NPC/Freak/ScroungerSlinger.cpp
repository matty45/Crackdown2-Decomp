#include "PHYSICS/physicsconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/characterconsts.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "gom/proto_registrar.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AI/Scrounger.h"
#include "AI/ScroungerSlinger.h"
#include "rws/classfactory.h"
#include "cd2/memory.h"
#include "AI/BehaviourClassID.h"
#include <new>

namespace AI
{
    const Fun_Runtime::cClass *ScroungerSlinger::ms_pScroungerSlingerClass = &ScroungerSlinger::StaticCreateClass();

    RWS::CAttributeHandler *ScroungerSlinger::SpawnFromPrototype(GOM::cObjectPrototype *, void *memory)
    {
        if (memory)
            return new (memory) ScroungerSlinger;
        return 0;
    }

    const Fun_Runtime::cClass &ScroungerSlinger::RetClass() const
    {
        return *ms_pScroungerSlingerClass;
    }

    RWS::CAttributeHandler *ScroungerSlinger::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new ScroungerSlingerPrototype(packet);
    }

    const char *ScroungerSlinger::RetClassName() const
    {
        return "ScroungerSlinger";
    }

    bool ScroungerSlinger::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pScroungerSlingerClass->IsA(c);
    }

    static RWS::CClassFactory::CRegistrar ScroungerSlingerRegistrar(
        "ScroungerSlinger", ScroungerSlinger::MakeNew, 0x140, false);

    Fun_Runtime::cClass &ScroungerSlinger::StaticCreateClass()
    {
        static Fun_Runtime::cClass *ScroungerSlingerClass = new Fun_Runtime::cClass(g_nBehaviourClassID++, "ScroungerSlinger", 0x140);
        return *ScroungerSlingerClass;
    }

    // CD2 0x82F94B80: runtime class inheritance registration.
    static Fun_Runtime::cInheritanceRegistrar ScroungerSlingerScroungerInheritRegistrar(
        AI::ScroungerSlinger::StaticCreateClass(), AI::Scrounger::StaticCreateClass());

    // CD2 0x82F94C38: register the class descriptor and placement factory.
    static GOM::cProtoRegistrar ScroungerSlingerSpawningRegistrar(
        ScroungerSlinger::StaticCreateClass(), ScroungerSlinger::SpawnFromPrototype);
}
