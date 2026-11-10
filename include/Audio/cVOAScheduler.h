#include "fun_runtime/class.h"
// Audio::cVOAScheduler (Crackdown 2): STAND-IN. Bases as in RuffKing's header: CD2's destructor (0x82837050) restores the
// vptrs at 0 (vtable 0x8215A420, whose slot 11 is RetClassName), 0x18 (CEventHandler) and 0x1C (cDebugPageHandler), unlinks
// RWS::iMsgRunningTick, clears ms_pInstance (0x838015F4) and runs the base destructors. Fields are not modelled.
#ifndef AUDIO_CVOASCHEDULER_H
#define AUDIO_CVOASCHEDULER_H

#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/dynamicallocationpolicy.h"
#include "GDb/cDebugPageHandler.h"
#include "rws/logic.h"
#include "cd2/memory.h"

#include "rws/attributes.h"

namespace Audio
{
    class cVOAScheduler : public RWS::CAttributeHandler, public RWS::CEventHandler, public RWS::DynamicAllocationPolicy,
                          public GDb::cDebugPageHandler
    {
    public:
        // CD2 0x82836EB8: the allocation factory calls this constructor out of line.
        cVOAScheduler();
        // CD2 0x82837050.
        virtual ~cVOAScheduler();
        // RuffKing declaration; CD2's event table installs the concrete handler at 0x828370E0.
        virtual void HandleEvents(RWS::CMsg &);
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x82836E00: registered-class virtual slot 1.
        virtual bool IsA(const Fun_Runtime::cClass &c) const;
        // RuffKing's singleton pointer (CD2 0x838015F4).
        static cVOAScheduler *ms_pInstance;
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x83012FA8);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cVOASchedulerClass = new Fun_Runtime::cClass(0x679, "cVOAScheduler", 0x480);
            return *cVOASchedulerClass;
        }
        // CD2 descriptor pointer 0x8392c9a4; its initializer names cVOAScheduler.
        static const Fun_Runtime::cClass *ms_pcVOASchedulerClass;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        // Descriptor and factory allocation agree on the complete size; own fields remain unrecovered.
        unsigned char m_unmodelled20[0x480 - 0x20];
        // CD2: cVOAScheduler's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x828370E0
    private:
        CD2_LAYOUT_CHECKS(cVOAScheduler, CD2_SIZE(cVOAScheduler, 0x480))
    };
}

#endif // AUDIO_CVOASCHEDULER_H
