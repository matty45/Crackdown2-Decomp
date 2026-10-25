// CHARACTER::cCharacterInterface (Crackdown 2): STAND-IN, sized to CD2; only what matched code needs so far. Evidence:
//   - Size 0xC0: cClass(0x5ED, "cCharacterInterface", 0xC0). Base cNonGameBase: its constructor 0x8254EC78 calls
//     cNonGameBase's.
//   - The constructor stores the vptr of Fun_Runtime::cSafeDeletablePointer<CHARACTER::cCharacter> m_pCharacter
//     (RuffKing name and type) at 0x7C and nulls that pointer's object pointer at 0x88 (RuffKing's
//     cSafeDeletablePointerBase:
//     cLinkedListItem, then m_pPtr at +0xC). The shared Fun_Runtime::cSafeDeletablePointerBase keeps that word private,
//     so the safe pointer is laid out flat here until it exposes it.
//   - RetCharacter is inline (no out-of-line copy in RuffKing or CD2): PLAYER::cPlayer::SetAITargeting reads 0x88,
//     null-tests it, subtracts 0x1C (cSafeDeletable's offset in cNonGameBase) and null-tests again.
#ifndef CHARACTER_CCHARACTERINTERFACE_H
#define CHARACTER_CCHARACTERINTERFACE_H

#include "gom/non_game_base.h"
#include "fun_runtime/safedeletable.h"
#include "CHARACTER/cCharacter.h"
#include "cd2/layout.h"

namespace CHARACTER
{
    class cCharacterInterface : public cNonGameBase
    {
    protected:
        unsigned char m_pCharacterLink[0xC];                // 0x7C: m_pCharacter's vptr and list links
        Fun_Runtime::cSafeDeletable *m_pCharacterPtr;       // 0x88: m_pCharacter's object pointer
    private:
        unsigned char m_pad8C[0xC0 - 0x8C];

    public:
        cCharacter *RetCharacter() const
        {
            return m_pCharacterPtr ? static_cast<cCharacter *>(m_pCharacterPtr) : 0;
        }

        CD2_LAYOUT_CHECKS(cCharacterInterface,
            CD2_SIZE(cCharacterInterface, 0xC0)
            CD2_OFFSET(cCharacterInterface, m_pCharacterPtr, 0x88))
    };
}

#endif // CHARACTER_CCHARACTERINTERFACE_H
