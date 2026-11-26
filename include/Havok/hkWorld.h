// STAND-IN: pointer-only Havok world API. CD2 0x823AD398 removes an entity and returns hkBool
// through a hidden result pointer. No complete layout is asserted or instantiated here.
#ifndef HAVOK_HKWORLD_H
#define HAVOK_HKWORLD_H
#include "Havok/hkBool.h"
class hkEntity;
class hkAction;
class hkPhantom;
class hkWorld
{
public:
    hkBool removeEntity(hkEntity *);
    void removeAction(hkAction *);
    // Havok's (RuffKing's) name and signature; CD2 0x82BCCF48, called by cPulse::Stop (0x8260F400).
    void removePhantom(hkPhantom *);
};
#endif
