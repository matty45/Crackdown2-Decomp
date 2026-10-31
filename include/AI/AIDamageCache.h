// AI::AIDamageCache: who damaged an AI player recently, and by how much. Layout and names from the RuffKing PDB
// (96 bytes: four 24-byte entries), confirmed in CD2: cAiPlayer's constructor (0x823E8650) builds it at 0x540 (the
// first field after cCharacterEntityIF), and cAiPlayer::RecallDamageCaused (0x823E8DC8, registered as the script
// method "RecallDamageCaused") inlines Read: it walks the four entries, compares each attacker (the safe pointer's
// object at +0xC, cast down to the character) with its argument and returns fDamage (+0x14).
// Read is __forceinline: CD2 expands it into RecallDamageCaused (RuffKing calls an out-of-line copy), and this compiler
// does not expand it as a plain inline member.
#ifndef AI_AIDAMAGECACHE_H
#define AI_AIDAMAGECACHE_H

#include "fun_runtime/safedeletablepointer.h"
#include "CHARACTER/cCharacter.h"
#include "cd2/layout.h"

namespace AI
{
    class AIDamageCache
    {
    public:
        struct tCacheEntry
        {
            Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> pAttacker;
            unsigned int nTimeStamp;
            float fDamage;

            CHARACTER::cCharacter *RetAttacker() const
            {
                return pAttacker.m_pPtr ? static_cast<CHARACTER::cCharacter *>(pAttacker.m_pPtr) : 0;
            }
        };

        AIDamageCache();

        // CD2 expands Flush, including safe-pointer assignment, into the constructor at 0x823E77C8.
        __forceinline void Flush()
        {
            for (unsigned char i = 0; i < nMAX_ATTACKER_CACHE_ENTRIES; ++i)
            {
                m_Cache[i].pAttacker = 0;
                m_Cache[i].fDamage = 0.0f;
                m_Cache[i].nTimeStamp = 0;
            }
        }

        __forceinline float Read(const CHARACTER::cCharacter *pCharacter) const
        {
            for (unsigned char i = 0; i < nMAX_ATTACKER_CACHE_ENTRIES; i++)
            {
                if (m_Cache[i].RetAttacker() == pCharacter)
                    return m_Cache[i].fDamage;
            }
            return 0.0f;
        }

    private:
        static const unsigned char nMAX_ATTACKER_CACHE_ENTRIES = 4;
        tCacheEntry m_Cache[nMAX_ATTACKER_CACHE_ENTRIES];

    public:
        CD2_LAYOUT_CHECKS(AIDamageCache,
            CD2_SIZE(AIDamageCache, 0x60)
            CD2_SIZE(tCacheEntry, 0x18)
            CD2_OFFSET(tCacheEntry, nTimeStamp, 0x10)
            CD2_OFFSET(tCacheEntry, fDamage, 0x14))
    };
}

#endif // AI_AIDAMAGECACHE_H
