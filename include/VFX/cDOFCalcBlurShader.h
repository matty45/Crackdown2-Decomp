// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// psDOFCalcBlur; vsDOFCalcBlur.
// Constructor 0x827955e0 installs the singleton at 0x83801108.
// Its callback getter 0x827955d0 returns 0x82795568; instance size is 0x64.
#ifndef VFX_CDOFCALCBLURSHADER_H
#define VFX_CDOFCALCBLURSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDOFCalcBlurShader : public cShader
    {
    public:
        static cDOFCalcBlurShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDOFCalcBlurShader, CD2_SIZE(cDOFCalcBlurShader, 0x64))
    };
}
#endif
