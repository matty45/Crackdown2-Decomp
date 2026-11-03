// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// PostProcessVS; SIMPLE_POST_PROCESS; PostProcessPS.
// Constructor 0x827db500 installs the singleton at 0x838012dc.
// Its callback getter 0x827db4f0 returns 0x827DB488; instance size is 0x64.
#ifndef VFX_CSIMPLEPOSTPROCESSSHADER_H
#define VFX_CSIMPLEPOSTPROCESSSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cSimplePostProcessShader : public cShader
    {
    public:
        static cSimplePostProcessShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cSimplePostProcessShader, CD2_SIZE(cSimplePostProcessShader, 0x64))
    };
}
#endif
