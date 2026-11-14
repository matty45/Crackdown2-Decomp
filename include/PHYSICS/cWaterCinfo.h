// STAND-IN: names/order from RuffKing cWave.cpp; CD2 water handler 0x82697740
// accesses the same 0x2C-byte settings block at 0x838465DC.
#ifndef PHYSICS_CWATERCINFO_H
#define PHYSICS_CWATERCINFO_H
#include "cd2/layout.h"
namespace PHYSICS
{
    class cWaterCinfo
    {
    public:
        float fWaterLevel;
        float fWaveAmplitude;
        float fWaveFrequency;
        float fWaveLength;
        float fWaveGradient;
        bool bUsingBuoyancy;
        float fWaterAngularDamping;
        float fWaterLinearDamping;
        float fWaterLinearFwdDamping;
        float fGroundLevel;
        float fMaxHeightLevel;
        CD2_LAYOUT_CHECKS(cWaterCinfo,
            CD2_SIZE(cWaterCinfo, 0x2C)
            CD2_OFFSET(cWaterCinfo, fWaveFrequency, 0x8)
            CD2_OFFSET(cWaterCinfo, bUsingBuoyancy, 0x14)
            CD2_OFFSET(cWaterCinfo, fWaterAngularDamping, 0x18)
            CD2_OFFSET(cWaterCinfo, fGroundLevel, 0x24)
            CD2_OFFSET(cWaterCinfo, fMaxHeightLevel, 0x28))
    };
}
#endif
