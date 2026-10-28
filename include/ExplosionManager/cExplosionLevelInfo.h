// STAND-IN: reference include/ref/ruffking/ExplosionManager_cExplosionLevelInfo.h.
// CD2's registrar at 0x82FD5440 gives size 0x80. The deleting destructor at
// 0x8263E6E0 resets this class's vptr and calls CAttributeHandler's destructor.
// Attribute offsets agree with the reference and CD2's factory at 0x8263E5E0.
#ifndef EXPLOSIONMANAGER_CEXPLOSIONLEVELINFO_H
#define EXPLOSIONMANAGER_CEXPLOSIONLEVELINFO_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/vec3.h"

namespace ExplosionManager
{
    class cExplosionLevelInfo : public RWS::CAttributeHandler
    {
        unsigned int m_nLevel;
        float m_fExplosionTime, m_fVFXScale, m_fFreakDeathVFXScale, m_fAcidVFXScale;
        float m_fAccumulationRadius, m_fMaxDamage, m_fMinDamage, m_fMaxForce;
        float m_fDamageRadius, m_fDecalRadius;
        int m_nExplosionEffectLevel;
        Fun_Runtime::Vec3 m_vDirectionOffset;
        float m_fExplosionSoundVolume;
        int m_nWaterExplosionVFXID, m_nUVExplosionVFXID, m_nAcidExplosionVFXID, m_nFreakDeathExplosionVFXID;
        float m_fCameraShakeAmount;

    public:
        cExplosionLevelInfo(const RWS::CAttributePacket &);
        virtual ~cExplosionLevelInfo() {}
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild();

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

        CD2_LAYOUT_CHECKS(cExplosionLevelInfo,
            CD2_SIZE(cExplosionLevelInfo, 0x80)
            CD2_OFFSET(cExplosionLevelInfo, m_nLevel, 0x18)
            CD2_OFFSET(cExplosionLevelInfo, m_vDirectionOffset, 0x50)
            CD2_OFFSET(cExplosionLevelInfo, m_fExplosionSoundVolume, 0x60)
            CD2_OFFSET(cExplosionLevelInfo, m_fCameraShakeAmount, 0x74))
    };
}

#endif
