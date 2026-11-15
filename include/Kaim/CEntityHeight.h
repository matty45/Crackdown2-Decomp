// Kaim::CEntityHeight (Crackdown 2): RuffKing's layout (kyentityheight.h): CEntityAttribute, then m_height at +4.
// CD2's cCharacterEntityIF::RetHeight (0x823F03E8) reads the float at +4 of the entity's height attribute with no call,
// so GetHeight is inline here.
#ifndef KAIM_CENTITYHEIGHT_H
#define KAIM_CENTITYHEIGHT_H

#include "Kaim/CEntityAttribute.h"
#include "cd2/layout.h"

namespace Kaim
{
    class CEntityHeight : public CEntityAttribute
    {
    public:
        float GetHeight() { return m_height; }
    private:
        float m_height;

        CD2_LAYOUT_CHECKS(CEntityHeight,
            CD2_SIZE(CEntityHeight, 0x8)
            CD2_OFFSET(CEntityHeight, m_height, 0x4))
    };
}

#endif // KAIM_CENTITYHEIGHT_H
