// STAND-IN: pointer-only Havok AABB phantom (Havok's hkAabbPhantom derives from hkPhantom). cPulse::Stop (0x8260F400)
// removes its phantom from the primary world and releases it through hkWorldObject::removeReference (0x82BD2300).
#ifndef HAVOK_HKAABBPHANTOM_H
#define HAVOK_HKAABBPHANTOM_H
#include "Havok/hkPhantom.h"
class hkAabbPhantom : public hkPhantom
{
};
#endif
