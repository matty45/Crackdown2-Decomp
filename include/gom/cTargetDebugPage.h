// GOM::cTargetDebugPage (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x8277DB60, from its registrars in CD2's
// initializer run); RuffKing names the class in cTargetDebugManager.obj. No layout or virtuals are modelled yet;
// base GDb::cDebugPageHandler from CD2's inheritance registrar.
#ifndef GOM_CTARGETDEBUGPAGE_H
#define GOM_CTARGETDEBUGPAGE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace GOM
{
    class cTargetDebugPage : public GDb::cDebugPageHandler
    {
    public:
        // CD2 0x8277DA58 / 0x8277DA68: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTargetDebugPageClass;
    };
}

#endif // GOM_CTARGETDEBUGPAGE_H
