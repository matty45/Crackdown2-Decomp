// VFX::cParticleEffectParent (Crackdown 2): STAND-IN. RuffKing's class (VFX/ParticleSystem/ParticleEffectParent.h,
// 0xA0 bytes) starts with its ParticleEffectParentPtr, then the skin-vertex count and skin-mesh array; the matrices and
// animation time after them are not modelled. CD2 inlines HasParent (a test of the parent pointer) wherever
// cParticleEffectInstance::SetAsOrphan is expanded, and the destructor (free the skin meshes, clear the pointer) in the
// instance's destruction (0x8245C7F0), so both are inline here.
#ifndef VFX_CPARTICLEEFFECTPARENT_H
#define VFX_CPARTICLEEFFECTPARENT_H

#include "VFX/ParticleEffectParentPtr.h"
#include "VFX/SkinMeshInfo.h"
#include "cd2/memory.h"

namespace VFX
{
    class cParticleEffectParent
    {
    private:
        ParticleEffectParentPtr m_Parent;   // 0x0
        unsigned int m_NumSkinVertices;     // 0x8
        SkinMeshInfo *m_pSkinMeshes;        // 0xC
        unsigned char m_unmodelled10[0xA0 - 0x10];
    public:
        ~cParticleEffectParent()
        {
            if (m_pSkinMeshes)
            {
                delete[] m_pSkinMeshes;
                m_pSkinMeshes = 0;
            }
        }
        bool HasParent() const { return m_Parent.Pointer != 0; }

        CD2_LAYOUT_CHECKS(cParticleEffectParent,
            CD2_SIZE(cParticleEffectParent, 0xA0)
            CD2_OFFSET(cParticleEffectParent, m_pSkinMeshes, 0xC))
    };
}

#endif // VFX_CPARTICLEEFFECTPARENT_H
