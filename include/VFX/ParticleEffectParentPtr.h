// VFX::ParticleEffectParentPtr (Crackdown 2): RuffKing's layout (VFX/ParticleSystem/ParticleEffectParent.h, 8 bytes):
// the parent's type, then its pointer. CD2's inlined cParticleEffectInstance::SetAsOrphan tests the pointer at +4 of the
// instance's parent (instance +0x84).
#ifndef VFX_PARTICLEEFFECTPARENTPTR_H
#define VFX_PARTICLEEFFECTPARENTPTR_H

#include "cd2/layout.h"

namespace CHARACTER { class cCharacter; }
namespace PHYSICS { class cBody; }

namespace VFX
{
    struct ParticleEffectParentPtr
    {
        enum
        {
            Type_Unknown = 0,
            Type_Character,
            Type_Body,
        } Type;
        union
        {
            CHARACTER::cCharacter *Character;
            PHYSICS::cBody *Body;
            void *Pointer;
        };

        CD2_LAYOUT_CHECKS(ParticleEffectParentPtr,
            CD2_SIZE(ParticleEffectParentPtr, 0x8)
            CD2_OFFSET(ParticleEffectParentPtr, Pointer, 0x4))
    };
}

#endif // VFX_PARTICLEEFFECTPARENTPTR_H
