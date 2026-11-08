// Core::cScheduler (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x825D3198, from its registrars in CD2's
// initializer run); RuffKing names the class in cScheduler.obj. No layout or virtuals are modelled yet;
// base GDb::cDebugPageHandler from CD2's inheritance registrar.
#ifndef CORE_CSCHEDULER_H
#define CORE_CSCHEDULER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace Core
{
    class cScheduler : public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSchedulerClass;
    };
}

#endif // CORE_CSCHEDULER_H
