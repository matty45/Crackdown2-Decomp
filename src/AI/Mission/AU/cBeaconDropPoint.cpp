// AI/Mission/AU/cBeaconDropPoint.cpp: RuffKing's Libraries/Shared/AI/Mission/AU/cBeaconDropPoint.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "AI/cBeaconDropPoint.h"
#include "cd2/memory.h"

namespace AI
{
    static RWS::CClassFactory::CRegistrar cBeaconDropPointRegistrar(
        "cBeaconDropPoint", cBeaconDropPoint::MakeNew, 0x60, false);
}
