// CHARACTER::cCwTransCharacter (Crackdown 2 only; Burn calls it cPlayerCharacter): STAND-IN, sized to CD2. Evidence:
// its StaticCreateClass builds cClass(0x6A1, "cCwTransCharacter", 0x2E00); its constructor 0x82231358 (its
// SpawnFromPrototype tail-calls it) calls cCharacter's constructor 0x82543408. CD2's cFrontEndAgent also derives from
// it.
#ifndef CHARACTER_CCWTRANSCHARACTER_H
#define CHARACTER_CCWTRANSCHARACTER_H

#include "CHARACTER/cCharacter.h"

namespace CHARACTER
{
    class cCwTransCharacter : public cCharacter
    {
    private:
        unsigned char m_pad2CC0[0x2E00 - 0x2CC0];

    public:
        CD2_LAYOUT_CHECKS(cCwTransCharacter,
            CD2_SIZE(cCwTransCharacter, 0x2E00))
    };
}

#endif // CHARACTER_CCWTRANSCHARACTER_H
