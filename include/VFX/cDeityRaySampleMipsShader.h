// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// psDeityRaySampleMips; vsDeityRaySampleMips.
// Constructor 0x82792400 installs the singleton at 0x83801100.
// Its callback getter 0x827923f0 returns 0x82792388; instance size is 0x64.
#ifndef VFX_CDEITYRAYSAMPLEMIPSSHADER_H
#define VFX_CDEITYRAYSAMPLEMIPSSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDeityRaySampleMipsShader : public cShader
    {
    public:
        static cDeityRaySampleMipsShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDeityRaySampleMipsShader, CD2_SIZE(cDeityRaySampleMipsShader, 0x64))
    };
}
#endif
