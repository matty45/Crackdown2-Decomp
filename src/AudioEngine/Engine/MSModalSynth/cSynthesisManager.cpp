// AudioEngine/Engine/MSModalSynth/cSynthesisManager.cpp: RuffKing's Libraries/Shared/Audio/Engine/MSModalSynth/cSynthesisManager.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "fun_runtime/inheritance_registrar.h"
#include "AudioEngine/cSynthesisManager.h"
#include "cd2/memory.h"

namespace AudioEngine
{
    Fun_Runtime::cClass &cSynthesisManager::StaticCreateClass()
    {
        static Fun_Runtime::cClass *cSynthesisManagerClass = new Fun_Runtime::cClass(0xD59F3B, "cSynthesisManager", 0x8);
        return *cSynthesisManagerClass;
    }

    const Fun_Runtime::cClass *cSynthesisManager::ms_pcSynthesisManagerClass = &cSynthesisManager::StaticCreateClass();

    static Fun_Runtime::cInheritanceRegistrar cSynthesisManagercDebugPageHandlerInheritRegistrar(
        cSynthesisManager::StaticCreateClass(), GDb::cDebugPageHandler::StaticCreateClass());
}
