// STAND-IN: descriptive name ours, from CD2 shader entries/defines:
// vsDOF; NUM_SAMPLES=7;; psDOF.
// Constructor 0x82795780 installs the singleton at 0x8380110c.
// Its callback getter 0x82795770 returns 0x82795708; instance size is 0x64.
#ifndef VFX_CDOFSHADER_H
#define VFX_CDOFSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cDOFShader : public cShader
    {
    public:
        static cDOFShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cDOFShader, CD2_SIZE(cDOFShader, 0x64))
    };
}
#endif
