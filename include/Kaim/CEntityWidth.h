// Kaim::CEntityWidth (Crackdown 2): RuffKing's layout (kyentitywidth.h): CEntityAttribute, then m_width at +4.
// CD2's cCharacterEntityIF::RetRadius (0x823F03F8) reads the float at +4 of the entity's width attribute with no call,
// so GetWidth is inline here.
#ifndef KAIM_CENTITYWIDTH_H
#define KAIM_CENTITYWIDTH_H

#include "Kaim/CEntityAttribute.h"
#include "cd2/layout.h"

namespace Kaim
{
    class CEntityWidth : public CEntityAttribute
    {
    public:
        float GetWidth() { return m_width; }
    private:
        float m_width;

        CD2_LAYOUT_CHECKS(CEntityWidth,
            CD2_SIZE(CEntityWidth, 0x8)
            CD2_OFFSET(CEntityWidth, m_width, 0x4))
    };
}

#endif // KAIM_CENTITYWIDTH_H
