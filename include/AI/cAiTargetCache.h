// AI::cAiTargetCache (Crackdown 2): RuffKing's class (AI/Targeting/cAiTargetCache.h): the owner and the current target
// info, 8 bytes. CD2 keeps it in cCharacterEntityIF at 0x4E0: the NPC behaviours read the target info at +0x4E4 of
// their host. Evidence:
//   - ClearTarget is CD2 0x8244D038 (26 callers): it releases and deletes the target info through its vtable, then
//     clears the pointer, as RuffKing's ClearTarget (SetTargetInfo(0)) does.
//   - SetTarget(position, flags) is CD2 0x8225CE90: CellMinigun::SetReactResupplyPoint (0x824C3D30) passes the
//     cache, the move-to position and 0, as RuffKing's does.
#ifndef AI_CAITARGETCACHE_H
#define AI_CAITARGETCACHE_H

#include "cd2/layout.h"

namespace Fun_Runtime { class Vec3; }

namespace AI
{
    class cCharacterEntityIF;
    class cAiTargetInfo;

    class cAiTargetCache
    {
    public:
        cAiTargetInfo *SetTarget(const Fun_Runtime::Vec3 &vecPosition, unsigned int nFlags);
        void ClearTarget();
        // RuffKing's accessor; CD2's behaviours test its result with cmpwi, as an inline accessor's.
        cAiTargetInfo *RetTargetInfo() const { return m_pTargetInfo; }

    private:
        cCharacterEntityIF *m_pOwner;           // 0x0
        cAiTargetInfo *m_pTargetInfo;           // 0x4

        CD2_LAYOUT_CHECKS(cAiTargetCache,
            CD2_SIZE(cAiTargetCache, 0x8)
            CD2_OFFSET(cAiTargetCache, m_pTargetInfo, 0x4))
    };
}

#endif // AI_CAITARGETCACHE_H
