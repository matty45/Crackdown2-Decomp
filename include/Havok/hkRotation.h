// hkRotation: an orthonormal hkMatrix3 (common/hkmath/linear/hkrotation.h). set(const hkQuaternion &) is out of line
// in CD2's hkmath.lib(hkRotation.obj), at 0x82BE1EB8 (IDENTITY_TRANSFORM's initializer calls it).
#ifndef HAVOK_HKROTATION_H
#define HAVOK_HKROTATION_H

#include "Havok/hkMatrix3.h"
#include "Havok/hkQuaternion.h"

class hkRotation : public hkMatrix3
{
public:
    void set(const hkQuaternion &q);
};

#endif // HAVOK_HKROTATION_H
