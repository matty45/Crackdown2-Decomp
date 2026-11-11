// STAND-IN: pointer-only Havok world API. CD2 0x823AD398 removes an entity and returns hkBool
// through a hidden result pointer. No complete layout is asserted or instantiated here.
#ifndef HAVOK_HKWORLD_H
#define HAVOK_HKWORLD_H
#include "Havok/hkBool.h"
class hkEntity;
class hkWorld
{
public:
    hkBool removeEntity(hkEntity *);
};
#endif
