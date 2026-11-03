// STAND-IN: descriptive name ours, from CD2 shader entries vsScatterUnpack / psScatterUnpack.
// Constructor 0x822B3950 installs the singleton at 0x838011B0 and links at +0x60.
// Getter 0x827AA638 returns callback 0x827AA5D0; instance size is 0x64.
#ifndef VFX_CSCATTERUNPACKSHADER_H
#define VFX_CSCATTERUNPACKSHADER_H
#include "VFX/cShader.h"
namespace VFX
{
    class cScatterUnpackShader : public cShader
    {
    public:
        static cScatterUnpackShader *ms_pInstance;
        static bool ReloadInstance(bool revert);
        virtual ReloadCallback GetReloadCallback() const;
        CD2_LAYOUT_CHECKS(cScatterUnpackShader, CD2_SIZE(cScatterUnpackShader, 0x64))
    };
}
#endif
