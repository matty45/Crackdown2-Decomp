// VFX::cParticleEffectInstance (Crackdown 2): STAND-IN. RuffKing's layout (VFX/ParticleSystem/cParticleEffectInstance.h,
// 0x130 bytes); only the members CD2's inlined code touches are modelled, at RuffKing's offsets. About a hundred CD2
// functions (most of them destructors: cGrenade's 0x8261E460, cCWWeapon's 0x82256348) expand the same sequence on an
// instance they own: StopEmitters (status flag 0x10 at +0x74, spawn-rate modifier +0x58 = CONST_FLOAT_0, read from
// cAgencyTowerSegmentMission's g_GlobalConstants copy 0x830B7F30, the object that holds these COMDATs), SetAsOrphan
// (when the parent pointer at +0x84 is set and the instance is not yet an orphan, link it at the head of
// ms_pOrphanRoot, 0x838012F0, through +0x120/+0x124) and Release (decrement the count at +0x70; at zero, call
// 0x8245C7F0, which unlinks the orphan, frees the nodes and the instance). RuffKing has StopEmitters, SetAsOrphan and
// Release; its Release deletes the instance, its SetAsOrphan calls DoSetAsOrphan out of line.
#ifndef VFX_CPARTICLEEFFECTINSTANCE_H
#define VFX_CPARTICLEEFFECTINSTANCE_H

#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "VFX/cParticleEffectParent.h"
#include "VFX/cParticleEffectResource.h"

namespace VFX
{
    class cParticleEffectInstance
    {
    private:
        unsigned char m_unmodelled0[0x40];
        const cParticleEffectResource *m_pResource;     // 0x40
        unsigned char m_unmodelled44[0x58 - 0x44];
        float m_SpawnRateMod;                           // 0x58
        unsigned char m_unmodelled5C[0x70 - 0x5C];
        unsigned int m_RefCount;                        // 0x70
        unsigned int m_StatusFlags;                     // 0x74
        unsigned char m_unmodelled78[0x80 - 0x78];
        cParticleEffectParent m_Parent;                 // 0x80
        cParticleEffectInstance **m_ppPrevOrphan;       // 0x120
        cParticleEffectInstance *m_pNextOrphan;         // 0x124
        unsigned char m_unmodelled128[0x130 - 0x128];
        static cParticleEffectInstance *ms_pOrphanRoot;
        // RuffKing's destructor (0x8293F2F8 there) without its assert. CD2 has no separate copy: its body is expanded
        // in the instance's deletion (0x8245C7F0), which Release calls.
        __forceinline ~cParticleEffectInstance()
        {
            if (m_ppPrevOrphan)
            {
                if (m_pNextOrphan)
                    m_pNextOrphan->m_ppPrevOrphan = m_ppPrevOrphan;
                *m_ppPrevOrphan = m_pNextOrphan;
            }
            FreeNodes();
            m_pResource->Release();
        }
        void FreeNodes();                               // CD2 0x822BB700
        void DoSetAsOrphan()
        {
            if (!m_ppPrevOrphan)
            {
                m_pNextOrphan = ms_pOrphanRoot;
                if (m_pNextOrphan)
                    m_pNextOrphan->m_ppPrevOrphan = &m_pNextOrphan;
                m_ppPrevOrphan = &ms_pOrphanRoot;
                ms_pOrphanRoot = this;
            }
        }
    public:
        void Release()
        {
            if (--m_RefCount == 0)
                delete this;
        }
        void StopEmitters()
        {
            m_SpawnRateMod = Fun_Runtime::g_GlobalConstants.CONST_FLOAT_0;
            m_StatusFlags |= 0x10;
        }
        unsigned int GetStatusFlags() const { return m_StatusFlags; }
        bool HasParent() const { return m_Parent.HasParent(); }
        void SetAsOrphan()
        {
            if (HasParent())
                DoSetAsOrphan();
        }

        CD2_LAYOUT_CHECKS(cParticleEffectInstance,
            CD2_SIZE(cParticleEffectInstance, 0x130)
            CD2_OFFSET(cParticleEffectInstance, m_pResource, 0x40)
            CD2_OFFSET(cParticleEffectInstance, m_SpawnRateMod, 0x58)
            CD2_OFFSET(cParticleEffectInstance, m_RefCount, 0x70)
            CD2_OFFSET(cParticleEffectInstance, m_StatusFlags, 0x74)
            CD2_OFFSET(cParticleEffectInstance, m_Parent, 0x80)
            CD2_OFFSET(cParticleEffectInstance, m_ppPrevOrphan, 0x120)
            CD2_OFFSET(cParticleEffectInstance, m_pNextOrphan, 0x124))
    };
}

#endif // VFX_CPARTICLEEFFECTINSTANCE_H
