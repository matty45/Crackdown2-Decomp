// STAND-IN: names and layout through nEquipmentID from the reference
// cExplosionManager header. CD2 constructor 0x82461278 confirms the offsets,
// identity matrix and zero decal vector for the initialized fields. CD2 additionally initializes the word
// at +0x78 to 3; its meaning is unknown, so its field name is ours.
// The constructor leaves nEquipmentID and vector/matrix fourth lanes untouched.
#ifndef EXPLOSIONMANAGER_TEXPLOSIONDATA_H
#define EXPLOSIONMANAGER_TEXPLOSIONDATA_H

#include "cd2/layout.h"
#include "fun_runtime/mtx.h"
#include "fun_runtime/vec3.h"
#include "ExplosionManager/eDetonationType.h"

class cGameBase;
namespace CHARACTER { class cCharacterInterface; }

namespace ExplosionManager
{
    struct tExplosionData
    {
        tExplosionData();
        Fun_Runtime::Mtx mTransform;
        unsigned int nLevel;
        bool bVisible;
        cGameBase *pInstigator;
        CHARACTER::cCharacterInterface *pAttacker;
        unsigned char nActivationType;
        eDetonationType eDT;
        unsigned short nMaterialId;
        unsigned short nChainLength;
        bool bApplyDecal;
        Fun_Runtime::Vec3 vDecalPos;
        bool bHEExplosion;
        unsigned int nEquipmentID; // Reference field; CD2 constructor leaves it untouched.
        unsigned int m_word78;

        CD2_LAYOUT_CHECKS(tExplosionData,
            CD2_SIZE(tExplosionData, 0x80)
            CD2_OFFSET(tExplosionData, mTransform, 0)
            CD2_OFFSET(tExplosionData, nLevel, 0x40)
            CD2_OFFSET(tExplosionData, bVisible, 0x44)
            CD2_OFFSET(tExplosionData, pInstigator, 0x48)
            CD2_OFFSET(tExplosionData, pAttacker, 0x4C)
            CD2_OFFSET(tExplosionData, nActivationType, 0x50)
            CD2_OFFSET(tExplosionData, eDT, 0x54)
            CD2_OFFSET(tExplosionData, nMaterialId, 0x58)
            CD2_OFFSET(tExplosionData, nChainLength, 0x5A)
            CD2_OFFSET(tExplosionData, bApplyDecal, 0x5C)
            CD2_OFFSET(tExplosionData, vDecalPos, 0x60)
            CD2_OFFSET(tExplosionData, bHEExplosion, 0x70)
            CD2_OFFSET(tExplosionData, nEquipmentID, 0x74)
            CD2_OFFSET(tExplosionData, m_word78, 0x78))
    };
}

#endif
