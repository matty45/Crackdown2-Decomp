// AI::cCharacterEntityIF (Crackdown 2): STAND-IN, sized to CD2. cClass(0x5F1, "cCharacterEntityIF", 0x540); its
// constructor 0x823EF240 calls cCharacterInterface's (0x8254EC78). Not modelled beyond its size.
#ifndef AI_CCHARACTERENTITYIF_H
#define AI_CCHARACTERENTITYIF_H

#include "CHARACTER/cCharacterInterface.h"

namespace AI
{
    class cCharacterEntityIF : public CHARACTER::cCharacterInterface
    {
    private:
        unsigned char m_padC0[0x540 - 0xC0];

    public:
        CD2_LAYOUT_CHECKS(cCharacterEntityIF,
            CD2_SIZE(cCharacterEntityIF, 0x540))
    };
}

#endif // AI_CCHARACTERENTITYIF_H
