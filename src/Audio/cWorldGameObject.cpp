// Audio/cWorldGameObject.cpp: RuffKing's Libraries/Shared/Audio/cWorldGameObject.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "Audio/cWorldGameObject.h"
#include "cd2/memory.h"

namespace Audio
{
    static RWS::CClassFactory::CRegistrar cWorldGameObjectRegistrar(
        "cWorldGameObject", cWorldGameObject::MakeNew, 0x1040, false);
}
