// VFX::cGlobalLight (Crackdown 2): STAND-IN. Name, flag enum and member names from RuffKing's
// VFX/cGlobalLightManager.h (size 0x80, virtual destructor at slot 0, m_nOcclusionIndex at 0x78, m_nFlags at 0x7B).
// CD2 evidence: SetOccluded (0x827FB518) reads the short at 0x78 and the occluded-light add/remove helpers
// (0x827FC2F0/0x827FC3B0) store it there; cVehicle::IsLightActive (0x826DE018) tests bit 1 (eLP_Damaged) of the byte
// at 0x7B. The fields before 0x78 are not recovered yet.
#ifndef VFX_CGLOBALLIGHT_H
#define VFX_CGLOBALLIGHT_H

#include "cd2/layout.h"

namespace VFX
{
    class cGlobalLight
    {
    public:
        enum etLightParams
        {
            eLP_On = (1 << 0),
            eLP_Damaged = (1 << 1),
            eLP_PulsingUp = (1 << 2),
            eLP_FadeIn = (1 << 3),
            eLP_FadeOut = (1 << 4),
            eLP_FadedOut = (1 << 5),
            eLP_CanRender = (1 << 6),
        };
        virtual ~cGlobalLight();
        void SetOccluded(bool bOccluded);
        // Inline in CD2: SetOccluded materialises this test twice. 512 is the occlusion-slot count
        // (RuffKing's m_aOcclusionData[512]; CD2's search loop in 0x827FC2F0 stops at 512).
        bool IsOccluded() { return m_nOcclusionIndex >= 0 && m_nOcclusionIndex < 512; }
        // Inlined by CD2 into cVehicle::IsLightActive.
        bool IsDamaged() const { return (m_nFlags & eLP_Damaged) != 0; }

    protected:
        unsigned char m_unmodelled04[0x78 - 4];
        short m_nOcclusionIndex;                // 0x78
        unsigned char m_unmodelled7A;
        unsigned char m_nFlags;                 // 0x7B
        unsigned char m_unmodelled7C[0x80 - 0x7C];

        CD2_LAYOUT_CHECKS(cGlobalLight,
            CD2_SIZE(cGlobalLight, 0x80)
            CD2_OFFSET(cGlobalLight, m_nOcclusionIndex, 0x78)
            CD2_OFFSET(cGlobalLight, m_nFlags, 0x7B))
    };
}

#endif // VFX_CGLOBALLIGHT_H
