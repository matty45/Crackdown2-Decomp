// Reconstructed inline reference release. Burn's hkConstraintData header includes
// hkreferencedobject.inl; CD2's cSpinningProp cleanup (0x8273F250) expands this body.
#ifndef HAVOK_HKREFERENCEDOBJECT_INL
#define HAVOK_HKREFERENCEDOBJECT_INL
#include "Havok/hkReferencedObject.h"
inline void hkReferencedObject::removeReference() const
{
    hkReferencedObject &object = const_cast<hkReferencedObject &>(*this);
    if (object.m_memSizeAndFlags && --object.m_referenceCount == 0)
        delete &object;
}
#endif
