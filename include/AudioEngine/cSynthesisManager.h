// AudioEngine::cSynthesisManager (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x825273E0, from its registrars in CD2's
// initializer run); RuffKing names the class in cSynthesisManager.obj. No layout or virtuals are modelled yet;
// base GDb::cDebugPageHandler from CD2's inheritance registrar.
#ifndef AUDIOENGINE_CSYNTHESISMANAGER_H
#define AUDIOENGINE_CSYNTHESISMANAGER_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "GDb/cDebugPageHandler.h"

namespace AudioEngine
{
    class cSynthesisManager : public GDb::cDebugPageHandler
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcSynthesisManagerClass;
    };
}

#endif // AUDIOENGINE_CSYNTHESISMANAGER_H
