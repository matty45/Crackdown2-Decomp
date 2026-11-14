// STAND-IN: Burn's namespace and both reference builds' fields. CD2 constructor
// 0x82756238 places the five pools after its four-byte release debug base, then
// the random generator at 0x90 and player at 0x98 (complete size 0x9C).
#ifndef ORB_CSKILLPICKUPMANAGER_H
#define ORB_CSKILLPICKUPMANAGER_H
#include "GDb/cDebugPageHandler.h"
#include "fun_runtime/randgen.h"
#include "ORB/eSkillPickupType.h"
#include "ORB/tSkillPickupData.h"
namespace PLAYER { class cPlayer; }
namespace ORB
{
    class cSkillPickup;
    class cSkillPickupManager : public GDb::cDebugPageHandler
    {
    public:
        struct tSkillPickupPool
        {
            cSkillPickup *aSkillPickup;
            unsigned short nCapacity;
            unsigned short nUsed;
            tSkillPickupData *pData;
            cSkillPickup *aDropping;
            unsigned short nNumDropping;
            cSkillPickup *aCollecting;
            unsigned short nNumCollecting;
            CD2_LAYOUT_CHECKS(tSkillPickupPool,
                CD2_SIZE(tSkillPickupPool, 0x1C)
                CD2_OFFSET(tSkillPickupPool, aSkillPickup, 0)
                CD2_OFFSET(tSkillPickupPool, nCapacity, 4)
                CD2_OFFSET(tSkillPickupPool, nUsed, 6)
                CD2_OFFSET(tSkillPickupPool, pData, 8)
                CD2_OFFSET(tSkillPickupPool, aDropping, 0xC)
                CD2_OFFSET(tSkillPickupPool, nNumDropping, 0x10)
                CD2_OFFSET(tSkillPickupPool, aCollecting, 0x14)
                CD2_OFFSET(tSkillPickupPool, nNumCollecting, 0x18))
        };
        tSkillPickupPool m_aSkillPickupPool[eSP_Num];
        Fun_Runtime::cRandGen m_RandGen;
        PLAYER::cPlayer *m_pPlayer;
        cSkillPickupManager();
        virtual ~cSkillPickupManager();
        void SetMaxPickups(eSkillPickupType, unsigned int);
        CD2_LAYOUT_CHECKS(cSkillPickupManager,
            CD2_SIZE(cSkillPickupManager, 0x9C)
            CD2_OFFSET(cSkillPickupManager, m_aSkillPickupPool, 4)
            CD2_OFFSET(cSkillPickupManager, m_RandGen, 0x90)
            CD2_OFFSET(cSkillPickupManager, m_pPlayer, 0x98))
    };
}
#endif
