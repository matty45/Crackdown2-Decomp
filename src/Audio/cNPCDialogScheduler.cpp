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
    "cNPCDialogScheduler", Audio::cNPCDialogScheduler::MakeNew, 0x7C, false);
