#ifndef AUDIO_CNPCDIALOGSCHEDULER_H
#define AUDIO_CNPCDIALOGSCHEDULER_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace Audio
{
    class cNPCDialogScheduler : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x83014230);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cNPCDialogSchedulerClass = new Fun_Runtime::cClass(0x67A, "cNPCDialogScheduler", 0x144);
            return *cNPCDialogSchedulerClass;
        }
        static const Fun_Runtime::cClass *ms_pcNPCDialogSchedulerClass;

        cNPCDialogScheduler();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

