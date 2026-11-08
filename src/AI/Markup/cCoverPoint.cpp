// AI/Markup/cCoverPoint.cpp: RuffKing's Libraries/Shared/AI/Markup/cCoverPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "AI/cCoverPoint.h"
#include "cd2/memory.h"

namespace AI
{
    static RWS::CClassFactory::CRegistrar cCoverPointRegistrar(
        "cCoverPoint", cCoverPoint::MakeNew, 0x40, false);
}
