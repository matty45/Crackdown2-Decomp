// STAND-IN: reference-named packed flag base of cActionManagerCharacterStateInfo, four bytes in both references.
// CD2 damage fields start at +4; the existing viewing-angle wrapper tests mask 0x40 in the second flag byte.
// Individual CD2 bit names remain unrecovered; keep their packed storage explicit.
#ifndef CHARACTER_CACTIONMANAGERCHARACTERCHARACTERSTATEINFOBOOLS_H
#define CHARACTER_CACTIONMANAGERCHARACTERCHARACTERSTATEINFOBOOLS_H

#include "cd2/layout.h"
namespace CHARACTER
{
    class cActionManagerCharacterCharacterStateInfoBools
    {
    public:
        unsigned char m_flags[4];
        CD2_LAYOUT_CHECKS(cActionManagerCharacterCharacterStateInfoBools,
            CD2_SIZE(cActionManagerCharacterCharacterStateInfoBools, 4)
            CD2_OFFSET(cActionManagerCharacterCharacterStateInfoBools, m_flags, 0))
    };
}
#endif
