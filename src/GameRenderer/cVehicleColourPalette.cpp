// GameRenderer/cVehicleColourPalette.cpp: RuffKing's Libraries/Shared/GameRenderer/cVehicleColourPalette.cpp.
// Set up from CD2's initializer run and the class registrars in it; the text range and its evidence are in
// config/splits.txt. Only the class statics and registrars are written so far.

#include "fun_runtime/class.h"
#include "rws/classfactory.h"
#include "GameRenderer/cVehicleColourPalette.h"
#include "cd2/memory.h"

namespace GameRenderer
{
    RWS::CAttributeHandler *cVehicleColourPalette::MakeNew(const RWS::CAttributePacket &packet, bool)
    {
        return new cVehicleColourPalette(packet);
    }

    const char *cVehicleColourPalette::RetClassName() const
    {
        return "cVehicleColourPalette";
    }

    static RWS::CClassFactory::CRegistrar cVehicleColourPaletteRegistrar(
        "cVehicleColourPalette", cVehicleColourPalette::MakeNew, 0xCC, false);
}
