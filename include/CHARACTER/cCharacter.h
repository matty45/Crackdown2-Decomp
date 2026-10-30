// CHARACTER::cCharacter (Crackdown 2): STAND-IN, sized to CD2. Only what matched code needs so far. Evidence:
//   - Size 0x2CC0: its StaticCreateClass builds cClass(0, "cCharacter", 0x2CC0); its constructor is 0x82543408.
//   - Bases: RuffKing's cCharacter derives from cCharacterMotion and others down to cGameBase; they are not modelled.
//     The stand-in derives from cNonGameBase, whose cSafeDeletable (0x1C) and cRegisteredClass (0x30) subobjects are
//     the ones matched code uses (the downcast from a safe pointer, and IsA).
//   - m_pTargeting (0x1524): cCwCharacterWrapper's constructor stores its TGT::cAiTargeting (0x2F40) there and its
//     PoiIF (0x2FA0) at 0x1528, RuffKing's m_pTargeting / m_pPoiIF pair (at 0x1534 / 0x1538 in RuffKing).
//   - m_eLODLevel (0x2812; RuffKing's unsigned char m_eLODLevel at 0x2822): cCharacterInterface's script method
//     "RetLODLevel" (0x8254E8C8) returns the character's byte at 0x2812, and cAiPlayer::ShouldTriggerFootStepEvent
//     (0x823EB518) compares it with 1, as RuffKing's does through RetLODLevel.
#ifndef CHARACTER_CCHARACTER_H
#define CHARACTER_CCHARACTER_H

#include "gom/non_game_base.h"
#include "TGT/cTargeting.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cCharacter : public cNonGameBase
    {
    private:
        unsigned char m_pad7C[0x548 - 0x7C];
    public:
        unsigned int m_field548;
    private:
        unsigned char m_pad54C[0x1524 - 0x54C];
    protected:
        TGT::cTargeting *m_pTargeting;          // 0x1524
    private:
        unsigned char m_pad1528[0x1681 - 0x1528];
    public:
        unsigned char m_byte1681;
    private:
        unsigned char m_pad1682[0x2812 - 0x1682];
    protected:
        unsigned char m_eLODLevel;              // 0x2812
    private:
        unsigned char m_pad2813[0x2CC0 - 0x2813];

    public:
        unsigned char RetLODLevel() const { return m_eLODLevel; }

        CD2_LAYOUT_CHECKS(cCharacter,
            CD2_SIZE(cCharacter, 0x2CC0)
            CD2_OFFSET(cCharacter, m_field548, 0x548)
            CD2_OFFSET(cCharacter, m_pTargeting, 0x1524)
            CD2_OFFSET(cCharacter, m_byte1681, 0x1681)
            CD2_OFFSET(cCharacter, m_eLODLevel, 0x2812))
    };
}

#endif // CHARACTER_CCHARACTER_H
