#ifndef GameManagement_cTagGameModePrototype_H
#define GameManagement_cTagGameModePrototype_H

#include "GameManagement/cPvPGameModePrototype.h"
#include "fun_runtime/stringc.h"

namespace GameManagement
{
    // RuffKing's base and members. CD2 MakeNew (0x82851F98, size 0x1D8) calls cPvPGameModePrototype's constructor
    // (0x8283E2F8), builds the two strings at 0x148/0x164 and clears the two durations at 0x180/0x184: RuffKing's
    // offsets plus 8, as the base is 0x148 bytes in CD2. Table 0x8215C590: RetStringID at 27, RetClassName at 42,
    // Destruct (the shared 0x8273FBA8 body) at 43.
    class cTagGameModePrototype : public cPvPGameModePrototype
    {
    public:
        // CD2 inlines this constructor into MakeNew.
        __forceinline cTagGameModePrototype() : m_fCarryScoreDuration(0.0f), m_fOrbRespawnDuration(0.0f) {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual int RetStringID() const;
    protected:
        Fun_Runtime::cStringc m_sItPrototypeName;
        Fun_Runtime::cStringc m_sItSecondaryName;
        float m_fCarryScoreDuration;
        float m_fOrbRespawnDuration;
        unsigned int m_nPickupInvulnTime_ms;
        unsigned int m_nPickupPoints;
        unsigned int m_nKillOrbCarrierPoints;
        unsigned int m_nKillChaserPoints;
        unsigned int m_nHoldOrbPoints;
        float m_fLowDamageFactor;
        float m_fDamageFactorRate;
        float m_fDamageFalloffRad;
        float m_fTrailMinScale;
        float m_fTrailMaxScale;
        float m_fOrbPulseMinScale;
        float m_fOrbPulseMaxScale;
        float m_fOrbPulseMinRate;
        float m_fOrbPulseMaxRate;
        float m_fOrbPulseStartTime;
        float m_fOrbDefaultScale;
        float m_fMapPingStartTime;
        float m_fMapPingScale;
        bool m_bMapPingFade;
        unsigned int m_nOrbCarrierMMColour;

        // CD2: cTagGameModePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x828521B8
        virtual GameManagement::etGameModeType RetType() const; // 14: 0x8288F788
        virtual void vf15(); // 15: 0x8288FB78
        virtual void vf16(); // 16: 0x827E56A8
        virtual void vf17(); // 17: 0x8288FB78
        virtual void vf18(); // 18: 0x8288FB78
        virtual void vf19(); // 19: 0x827E56A8
        virtual void vf23(); // 23: 0x8288FB78
        virtual void vf24(); // 24: 0x8288FB78
        virtual void vf25(); // 25: 0x82889A60
        virtual void vf26(); // 26: 0x8288D5C0
        virtual void vf40(); // 40: 0x828520F0
    protected:
        CD2_LAYOUT_CHECKS(cTagGameModePrototype,
            CD2_SIZE(cTagGameModePrototype, 0x1D8)
            CD2_OFFSET(cTagGameModePrototype, m_sItPrototypeName, 0x148)
            CD2_OFFSET(cTagGameModePrototype, m_sItSecondaryName, 0x164)
            CD2_OFFSET(cTagGameModePrototype, m_fCarryScoreDuration, 0x180)
            CD2_OFFSET(cTagGameModePrototype, m_nOrbCarrierMMColour, 0x1D4))
    };
}

#endif
