// VFX::SkinMeshInfo (Crackdown 2): RuffKing's layout (its PDB, 0x24 bytes). cParticleEffectParent owns an array of them;
// CD2's particle-instance destruction (0x8245C7F0) frees that array.
#ifndef VFX_SKINMESHINFO_H
#define VFX_SKINMESHINFO_H

#include "cd2/layout.h"

struct D3DVertexBuffer;

namespace VFX
{
    struct SkinMeshInfo
    {
        unsigned int NumVertices;
        unsigned int Stride;
        unsigned int PosOffset;
        unsigned int NormOffset;
        unsigned int IndicesOffset;
        unsigned int WeightsOffset;
        D3DVertexBuffer *VertexBuffer;
        unsigned char *VertexData;
        bool bPosIsFloat3;

        CD2_LAYOUT_CHECKS(SkinMeshInfo,
            CD2_SIZE(SkinMeshInfo, 0x24))
    };
}

#endif // VFX_SKINMESHINFO_H
