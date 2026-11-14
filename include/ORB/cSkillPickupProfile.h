#ifndef ORB_cSkillPickupProfile_H
#define ORB_cSkillPickupProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/vec3.h"
#include "ORB/tSkillPickupData.h"

namespace ORB
{
    class cSkillPickupProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82756D70 (MakeNew calls it).
        cSkillPickupProfile();
        // CD2 deleting wrapper 0x82756E88 clears the singleton before base cleanup.
        virtual ~cSkillPickupProfile();
        // CD2's table 0x82145DB4 has distinct attribute and design-build entries.
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild() { return true; }
        // Burn/RuffKing names; CD2 constructor 0x82756D70 stores these offsets
        // and publishes this to the singleton at 0x83800FCC.
        static cSkillPickupProfile *RetSingleton() { return ms_pSingleton; }
        float m_fCollectedRadSq;
        float m_fCollectionAcceleration;
        float m_fMinDropDistance;
        float m_fMaxDropDistance;
        float m_fTimeToDestinationPerMeter;
        float m_fOneOverK;
        Fun_Runtime::Vec3 m_vecKGOver2;
        Fun_Runtime::Vec3 m_vecGravity;
        int m_nAbsorbEffectId;
        int m_nSkinGlowEffectId;
        unsigned int m_nSkinGlowFadeDuration;
        tSkillPickupData m_aSkillPickupData[5];
        float m_fEffectScale;
    private:
        static cSkillPickupProfile *ms_pSingleton;
        CD2_LAYOUT_CHECKS(cSkillPickupProfile,
            CD2_SIZE(cSkillPickupProfile, 0xB0)
            CD2_OFFSET(cSkillPickupProfile, m_fCollectedRadSq, 0x18)
            CD2_OFFSET(cSkillPickupProfile, m_fCollectionAcceleration, 0x1C)
            CD2_OFFSET(cSkillPickupProfile, m_fMinDropDistance, 0x20)
            CD2_OFFSET(cSkillPickupProfile, m_fMaxDropDistance, 0x24)
            CD2_OFFSET(cSkillPickupProfile, m_fTimeToDestinationPerMeter, 0x28)
            CD2_OFFSET(cSkillPickupProfile, m_fOneOverK, 0x2C)
            CD2_OFFSET(cSkillPickupProfile, m_vecKGOver2, 0x30)
            CD2_OFFSET(cSkillPickupProfile, m_vecGravity, 0x40)
            CD2_OFFSET(cSkillPickupProfile, m_nAbsorbEffectId, 0x50)
            CD2_OFFSET(cSkillPickupProfile, m_nSkinGlowEffectId, 0x54)
            CD2_OFFSET(cSkillPickupProfile, m_nSkinGlowFadeDuration, 0x58)
            CD2_OFFSET(cSkillPickupProfile, m_aSkillPickupData, 0x5C)
            CD2_OFFSET(cSkillPickupProfile, m_fEffectScale, 0xAC))

    };
}

#endif
