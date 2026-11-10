// STAND-IN: GangManager::cFactionInfo. CD2's runtime descriptor (initializer 0x82FDCB50: cClass(0x40E,
// "cFactionInfo", 0x220)) gives its size. CD2's constructor (0x826766E0) stores cScriptHost's tables at 0 and 0x14,
// so CD2's class derives from cScriptHost (RuffKing's has a bare vptr). Members and names follow RuffKing's
// cFactionInfo.h, each 0xC bytes later in CD2 (cScriptHost's 0x1C against RuffKing's vptr + 0xC); the offsets are
// confirmed by the constructor's stores (defaults 30/0/10/2/5/5, nID at 0x60, the name string's empty state at 0x64,
// m_nEnforcerRatingForLevel's loop at 0xA4) and by cFactionConfigData::HandleAttributes (0x1C, 0x98, 0xA4).
// RuffKing's members are private; they are public here because cFactionConfigData's inlined setup writes them.
// The gang list (RuffKing cVectorip<cGangInfo *, 80> at 0xBC) and the spawning flag are not modelled yet: opaque.
#ifndef GANGMANAGER_CFACTIONINFO_H
#define GANGMANAGER_CFACTIONINFO_H

#include "fun_runtime/scripthost.h"
#include "fun_runtime/stringc.h"
#include "cd2/layout.h"

namespace AI
{
    struct tAIFactionTargetData;
}

namespace GangManager
{
    enum etRelationship
    {
        eEnemy = -1,
        eNeutral = 0,
        eFriend
    };

    class cFactionInfo : public Fun_Runtime::cScriptHost
    {
    public:
        static const Fun_Runtime::cClass *ms_pcFactionInfoClass;
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer.
            static Fun_Runtime::cClass *descriptor = new Fun_Runtime::cClass(0x40E, "cFactionInfo", 0x220);
            return *descriptor;
        }

        virtual const char *RetName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        int m_nMaxEnforcerRating;
        int m_DecrimentTimer;
        int m_nEnforcerIdleDecrementTime;
        int m_nEnforcerIdleDecrementWaitTime;
        int m_nEnforcerActiveDecrementTime;
        int m_nEnforcerInvulnerableTime;
        bool m_bForceMaxEnforcerRating;
        float m_EnforcerRating[8];
        bool m_bEnforcerRatingOn[8];
        unsigned int m_nID;
        Fun_Runtime::cStringc m_sName;
        etRelationship m_anGangRelationship[6];
        const AI::tAIFactionTargetData *m_pTargetingData;
        unsigned char m_nEnforcerLevel[8];
        int m_nEnforcerRatingForLevel[6];
    private:
        unsigned char m_unmodelledBC[0x220 - 0xBC];

    public:
        CD2_LAYOUT_CHECKS(cFactionInfo,
            CD2_SIZE(cFactionInfo, 0x220)
            CD2_OFFSET(cFactionInfo, m_nMaxEnforcerRating, 0x1C)
            CD2_OFFSET(cFactionInfo, m_nEnforcerInvulnerableTime, 0x30)
            CD2_OFFSET(cFactionInfo, m_bEnforcerRatingOn, 0x58)
            CD2_OFFSET(cFactionInfo, m_nID, 0x60)
            CD2_OFFSET(cFactionInfo, m_sName, 0x64)
            CD2_OFFSET(cFactionInfo, m_anGangRelationship, 0x80)
            CD2_OFFSET(cFactionInfo, m_pTargetingData, 0x98)
            CD2_OFFSET(cFactionInfo, m_nEnforcerRatingForLevel, 0xA4))
    };
}

#endif // GANGMANAGER_CFACTIONINFO_H
