// STAND-IN: reference-named water-state enum. Values are not yet recovered or used by matched code.
#ifndef CHARACTER_EWATERSURFACESTATE_H
#define CHARACTER_EWATERSURFACESTATE_H
// Values from Burn's declaration; CD2's simple controller (0x82564620) reports eWSS_On while in water.
namespace CHARACTER
{
    enum eWaterSurfaceState
    {
        eWSS_None = 0,
        eWSS_Above,
        eWSS_On,
        eWSS_Below,
    };
}
#endif
