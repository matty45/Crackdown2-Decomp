// GameRenderer::cVehicleColourPalette (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8266B008, from its registrars in CD2's
// initializer run); RuffKing names the class in cVehicleColourPalette.obj. No layout or virtuals are modelled yet.
#ifndef GAMERENDERER_CVEHICLECOLOURPALETTE_H
#define GAMERENDERER_CVEHICLECOLOURPALETTE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace GameRenderer
{
    class cVehicleColourPalette
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // GAMERENDERER_CVEHICLECOLOURPALETTE_H
