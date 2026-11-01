// VFX::cParticleEffectManager (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in RuffKing's
// header; RetClassName (0x827DEDF8) is slot 11 of the vtable at 0x820098B8, as cNonGameBase's RetClassName.
#ifndef VFX_CPARTICLEEFFECTMANAGER_H
#define VFX_CPARTICLEEFFECTMANAGER_H

#include "gom/non_game_base.h"

namespace VFX
{
    class cParticleEffectManager : public cNonGameBase
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif // VFX_CPARTICLEEFFECTMANAGER_H
