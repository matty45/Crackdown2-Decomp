// GameRenderer::cVehicleColourPalette (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x8266B008, from its registrars in CD2's
// initializer run); RuffKing names the class in cVehicleColourPalette.obj. No layout or virtuals are modelled yet.
#ifndef GAMERENDERER_CVEHICLECOLOURPALETTE_H
#define GAMERENDERER_CVEHICLECOLOURPALETTE_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "fun_runtime/randgen.h"

namespace GameRenderer
{
    class cVehicleColourPalette : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x8266B008 constructs the CAttributeHandler base inline. Its table at
        // 0x8212E49C adds RetClassName at slot 11 and Destruct at slot 12, as in RuffKing.
        // CD2 folds construction into its allocation factory without a constructor call.
        cVehicleColourPalette(const RWS::CAttributePacket &) : m_colourIndex(0)
        {
            ms_pVehicleColourPalette = this;
        }
        virtual ~cVehicleColourPalette();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual const char *RetClassName() const;
        virtual void Destruct();

    private:
        // RuffKing names the palette, index and generator. CD2 retains 42 colours:
        // the index and the two default-zero generator words are at 0xC0..0xC8.
        unsigned int m_vehicleColourPalette[42];
        unsigned int m_colourIndex;
        Fun_Runtime::cRandGen m_RandomNumGen;
        static cVehicleColourPalette *ms_pVehicleColourPalette;

        CD2_LAYOUT_CHECKS(cVehicleColourPalette,
            CD2_SIZE(cVehicleColourPalette, 0xCC)
            CD2_OFFSET(cVehicleColourPalette, m_vehicleColourPalette, 0x18)
            CD2_OFFSET(cVehicleColourPalette, m_colourIndex, 0xC0)
            CD2_OFFSET(cVehicleColourPalette, m_RandomNumGen, 0xC4))
    };
}

#endif // GAMERENDERER_CVEHICLECOLOURPALETTE_H
