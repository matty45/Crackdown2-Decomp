// STAND-IN: Havok shape phantom, named by Burn's and RuffKing's declarations of the simple character controller's
// m_pPhantom. CD2's RetPtrShape (0x82565A80) and RetPtrCollidable (0x82565A90) reach its collidable at +0x14
// through hkWorldObject. Used through pointers only; its own slots and size are not modelled.
#ifndef HAVOK_HKSHAPEPHANTOM_H
#define HAVOK_HKSHAPEPHANTOM_H
#include "Havok/hkPhantom.h"
class hkShapePhantom : public hkPhantom
{
};
#endif
