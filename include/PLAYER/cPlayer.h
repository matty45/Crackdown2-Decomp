// PLAYER::cPlayer (Crackdown 2): STAND-IN, sized to CD2; only what matched code needs, the rest is padding. Evidence:
//   - Size 0x1160: StaticCreateClass 0x8271F198 builds cClass(4, "cPlayer", 0x1160). RuffKing's cPlayer (0x680 bytes)
//     is laid out differently.
//   - Bases: AI::cCharacterEntityIF first, as in RuffKing. The other bases start at 0x540 (the constructor 0x8271F7C8
//     stores vptrs at 0x540, 0x544 and 0x548; RuffKing: GDb::cDebugPageHandler, SaveGame::cLoadSaveObject,
//     cPlayerSystemInterface) and are not modelled: padding.
//   - m_bIsAIActive (0xD90; RuffKing's name) and m_bIsAITargeting (0xD91; the name is ours, after the script method):
//     cPlayer's script methods (registered in 0x8271F230) are "SetAIActive" (0x82724980: stores 0xD90, then re-applies
//     SetAITargeting with 0xD91), "IsAIActive" (0x82724990: returns 0xD90), "SetAITargeting" (0x82724998: stores 0xD91)
//     and "IsAITargeting" (0x82724A28: returns 0xD91). RuffKing has m_bIsAIActive only.
#ifndef PLAYER_CPLAYER_H
#define PLAYER_CPLAYER_H

#include "AI/cCharacterEntityIF.h"
#include "CHARACTER/cCwTransCharacterWrapper.h"
#include "cd2/layout.h"

namespace PLAYER
{
    class cPlayer : public AI::cCharacterEntityIF
    {
    private:
        unsigned char m_pad540[0xD90 - 0x540];
    protected:
        bool m_bIsAIActive;         // 0xD90
        bool m_bIsAITargeting;      // 0xD91
    private:
        unsigned char m_padD92[0x1160 - 0xD92];

    public:
        void SetAITargeting(bool bAITargeting);

        CD2_LAYOUT_CHECKS(cPlayer,
            CD2_SIZE(cPlayer, 0x1160)
            CD2_OFFSET(cPlayer, m_bIsAIActive, 0xD90)
            CD2_OFFSET(cPlayer, m_bIsAITargeting, 0xD91))
    };
}

#endif // PLAYER_CPLAYER_H
