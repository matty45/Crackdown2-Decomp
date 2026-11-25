// GameRenderer::cLODClump and GameRenderer::cClump (Crackdown 2): STAND-INS for the members CD2's inlined accessors
// reach. Names and order from RuffKing's GameRenderer/cLODClump.h and cClump.h; offsets are CD2's:
// - cLODClump keeps one cClump per buffer, indexed by GameRenderer::g_nGameIndex (CD2 0x83800D28; RuffKing defines it
//   in cTestRenderer.cpp). CD2's code reaches the current one at +0x80 + 0x320 * g_nGameIndex (cVehicle's Show,
//   0x826CFE90; cPhantomBody 0x8268AA80 copies the body matrix to +0x80), so CD2's cClump is 0x320 bytes (RuffKing's
//   is 0x280) and the clumps start at 0x80 (RuffKing: 0x60).
// - cClump: m_BaseMatrix at 0 (the matrix 0x8268AA80 stores); m_nRootNode and m_nNumFrames at 0x48/0x49 and m_bVisible
//   at 0x58, 4 bytes above RuffKing's (cVehicle slot 398, 0x826D48D0, bounds a frame index by them; Show stores the
//   flag); m_Frames at 0x118: its 130 entries end the class at 0x320.
// - SetVisibility and GetGameVisibility: RuffKing's SetVisibility (0x8276EE08) stores the flag of the current clump and
//   sets dirty bit 2; CD2 expands both inline in every caller (Show; cStaticEnvironment 0x82809550; cEquipment's
//   GetVisibility 0x82605A18, which RuffKing's 0x826C3570 also reads directly).
#ifndef GAMERENDERER_CLODCLUMP_H
#define GAMERENDERER_CLODCLUMP_H

#include "cd2/layout.h"
#include "fun_runtime/mtx.h"

class cGameBase;

namespace GameRenderer
{
    class cFrameData;

    // RuffKing's name and type (cTestRenderer.cpp): the buffer the game side writes.
    extern unsigned int g_nGameIndex;

    class cClump
    {
    public:
        void SetBaseMtx(const Fun_Runtime::Mtx &mtx)
        {
            m_BaseMatrix = mtx;
        }

        Fun_Runtime::Mtx m_BaseMatrix;                      // 0x0
    private:
        unsigned char m_unknown40[0x48 - 0x40];
    public:
        unsigned char m_nRootNode;                          // 0x48
        unsigned char m_nNumFrames;                         // 0x49
    private:
        unsigned char m_unknown4A[0x58 - 0x4A];
    public:
        bool m_bVisible;                                    // 0x58
        char m_nForceLOD;                                   // 0x59: cLOD4Environment's LockLOD (0x82807FC8)
    private:
        unsigned char m_unknown5A[0x118 - 0x5A];
    public:
        cFrameData *m_Frames[130];                          // 0x118

        CD2_LAYOUT_CHECKS(cClump,
            CD2_SIZE(cClump, 0x320)
            CD2_OFFSET(cClump, m_nRootNode, 0x48)
            CD2_OFFSET(cClump, m_bVisible, 0x58)
            CD2_OFFSET(cClump, m_nForceLOD, 0x59)
            CD2_OFFSET(cClump, m_Frames, 0x118))
    };

    class cLODClump
    {
    public:
        // RuffKing's flags (cLODClump.h).
        enum eDirtyFlags
        {
            eDF_cLODClump_TermLOD = (1 << 0),
            eDF_cLODClump_SetVisibility = (1 << 1),
            eDF_cLODClump_SetAllFrameVisibility = (1 << 2),
            eDF_cLODClump_SetDMorphProportion = (1 << 3),
            eDF_cLODClump_SetDMorphProportion2 = (1 << 4),
            eDF_cLODClump_InitLOD = (1 << 5),
            eDF_cLODClump_RefreshGraphics = (1 << 6),
            eDF_cLODClump_RemoveGraphics = (1 << 7),
            eDF_cLODClump_SetPartsVisible = (1 << 8),
            eDF_cLODClump_SetMorphAnimTime = (1 << 9),
            eDF_cLODClump_AddMorphAnimTime = (1 << 10),
            eDF_cLODClump_SetAnim = (1 << 11),
            eDF_cLODClump_SetAnimEventSeq = (1 << 12),
            eDF_cLODClump_SetAnimTime = (1 << 13),
            eDF_cLODClump_AddAnimTime = (1 << 14),
            eDF_cLODClump_SetLooping = (1 << 15),
            eDF_cLODClump_SetTransform = (1 << 16),
            eDF_cLODClump_SetFadeOverride = (1 << 17),
            eDF_cFrame_SetIsVisible = (1 << 18),
            eDF_cFrame_SetGameTransform = (1 << 19),
            eDF_HUD_Update = (1 << 20),
            eDF_SetEmissive = (1 << 21),
            eDF_cLODClump_SetForceLOD = (1 << 22),
        };

        void SetDirty(eDirtyFlags eFlag)
        {
            m_nDirtyFlags |= eFlag;
        }

        void SetVisibility(bool bVisible)
        {
            if (bVisible != m_LODClumps[g_nGameIndex].m_bVisible)
            {
                m_LODClumps[g_nGameIndex].m_bVisible = bVisible;
                SetDirty(eDF_cLODClump_SetVisibility);
            }
        }

        void SetForceLOD(char nLOD)
        {
            m_LODClumps[g_nGameIndex].m_nForceLOD = nLOD;
            SetDirty(eDF_cLODClump_SetForceLOD);
        }

        void ClearForceLOD()
        {
            SetForceLOD(-1);
        }

        bool GetGameVisibility() const
        {
            return m_LODClumps[g_nGameIndex].m_bVisible;
        }

        unsigned int m_nID;                                 // 0x0
        cGameBase *m_pGameBase;                             // 0x4
        unsigned int m_nDirtyFlags;                         // 0x8
    private:
        unsigned char m_unknownC[0x80 - 0xC];
    public:
        cClump m_LODClumps[2];                              // 0x80

        CD2_LAYOUT_CHECKS(cLODClump,
            CD2_OFFSET(cLODClump, m_nDirtyFlags, 0x8)
            CD2_OFFSET(cLODClump, m_LODClumps, 0x80))
    };
}

#endif // GAMERENDERER_CLODCLUMP_H
