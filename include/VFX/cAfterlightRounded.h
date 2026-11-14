// VFX::cAfterlightRounded (Crackdown 2): STAND-IN for the free function that releases one; the class layout is not
// modelled. RuffKing's cafterlight.cpp defines bool FreeALRounded(cAfterlightRounded **) (0x828E3BD8 there); CD2's
// copy is 0x8278EB68 (15 callers), which cLandVehicle's TurnOffVehicleLights (0x826C5308) calls with the address of
// each of its two headlight afterlights, as RuffKing's does.
#ifndef VFX_CAFTERLIGHTROUNDED_H
#define VFX_CAFTERLIGHTROUNDED_H

namespace VFX
{
    class cAfterlightRounded;
    bool FreeALRounded(cAfterlightRounded **ppAfterlight);
}

#endif // VFX_CAFTERLIGHTROUNDED_H
