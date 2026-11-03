// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// PostProcessPS; PostProcessVS.
// Constructor 0x827db360 installs the singleton at 0x838012d8.
// Its callback getter 0x827db350 returns 0x827DB2E8; instance size is 0x64.
#ifndef VFX_CPOSTPROCESSSHADER_H
#define VFX_CPOSTPROCESSSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cPostProcessShader : public cShader
    {
    public:
        static cPostProcessShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cPostProcessShader, CD2_SIZE(cPostProcessShader, 0x64))
    };
}
#endif
