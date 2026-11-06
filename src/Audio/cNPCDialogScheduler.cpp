// Header constants: CD2's initializer run for this object shows these headers' constants in this order. RuffKing's
// object gets them through its other headers (docs/matching-notes.md, "Header constants"); included directly here.
#include "PHYSICS/physicsconsts.h"
#include "CHARACTER/characterconsts.h"
#include "PHYSICS/physicsproject.h"
#include "CHARACTER/cCharacterController.h"
#include "CHARACTER/cRagdollProfile.h"
#include "AI/aiconstants.h"
#include "Audio/cNPCDialogScheduler.h"
#include "rws/classfactory.h"

namespace Audio
{
    const Fun_Runtime::cClass *cNPCDialogScheduler::ms_pcNPCDialogSchedulerClass = 0;

    cNPCDialogScheduler::cNPCDialogScheduler() {}

    const Fun_Runtime::cClass &cNPCDialogScheduler::RetClass() const
    {
        return *ms_pcNPCDialogSchedulerClass;
    }

    const char *cNPCDialogScheduler::RetClassName() const
    {
        return "cNPCDialogScheduler";
    }

    bool cNPCDialogScheduler::IsA(const Fun_Runtime::cClass &c) const
    {
        return ms_pcNPCDialogSchedulerClass->IsA(c);
    }

    RWS::CAttributeHandler *cNPCDialogScheduler::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cNPCDialogScheduler();
    }
}

static RWS::CClassFactory::CRegistrar cNPCDialogSchedulerRegistrar(
    "cNPCDialogScheduler", Audio::cNPCDialogScheduler::MakeNew, 0x144, false);
