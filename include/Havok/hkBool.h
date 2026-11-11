// Havok's byte-sized boolean wrapper, from RuffKing's hkbasetypes.h.
// CD2 hkWorld::removeEntity (0x823AD398) receives a hidden result pointer and writes one byte.
#ifndef HAVOK_HKBOOL_H
#define HAVOK_HKBOOL_H
#include "cd2/layout.h"
class hkBool
{
public:
    hkBool(bool value) : m_bool(value) {}
    hkBool() {}
    operator bool() const { return m_bool != 0; }
    hkBool operator==(bool value) const { return hkBool(m_bool == value); }
private:
    char m_bool;
    CD2_LAYOUT_CHECKS(hkBool, CD2_SIZE(hkBool, 1) CD2_OFFSET(hkBool, m_bool, 0))
};
#endif
