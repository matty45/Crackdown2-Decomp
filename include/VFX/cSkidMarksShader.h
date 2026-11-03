// STAND-IN: descriptive name ours, from CD2 shader entries vsSkidMarks / psSkidMarks.
// Constructor 0x821D6308 installs the singleton at 0x83801210 and links at +0x60.
// Getter 0x827B7B50 returns callback 0x827B7AE8; instance size is 0x64.
#ifndef VFX_CSKIDMARKSSHADER_H
#define VFX_CSKIDMARKSSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cSkidMarksShader : public cShader
    {
    public:
        static cSkidMarksShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cSkidMarksShader, CD2_SIZE(cSkidMarksShader, 0x64))
    };
}
#endif
