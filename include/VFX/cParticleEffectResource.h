// VFX::cParticleEffectResource (Crackdown 2): STAND-IN. RuffKing's class (VFX/ParticleSystem/cParticleEffectResource.h,
// 0x44 bytes): only the reference count at +0x1C is modelled. CD2's particle-instance destruction (0x8245C7F0)
// decrements it and, when its low 31 bits reach zero, destroys the resource (0x827EDE20, out of line) and frees it, as
// RuffKing's ~cParticleEffectInstance does through Release.
#ifndef VFX_CPARTICLEEFFECTRESOURCE_H
#define VFX_CPARTICLEEFFECTRESOURCE_H

#include "cd2/layout.h"
#include "cd2/memory.h"

namespace VFX
{
    class cParticleEffectResource
    {
    private:
        unsigned char m_unmodelled0[0x1C];
        mutable unsigned int m_RefCount;    // 0x1C
        unsigned char m_unmodelled20[0x44 - 0x20];
        ~cParticleEffectResource();
    public:
        void Release() const
        {
            if ((--m_RefCount & 0x7FFFFFFF) == 0)
                delete this;
        }

        CD2_LAYOUT_CHECKS(cParticleEffectResource,
            CD2_SIZE(cParticleEffectResource, 0x44)
            CD2_OFFSET(cParticleEffectResource, m_RefCount, 0x1C))
    };
}

#endif // VFX_CPARTICLEEFFECTRESOURCE_H
