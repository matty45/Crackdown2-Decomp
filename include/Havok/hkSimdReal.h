// Reference Havok SIMD scalar: one vector, scalar/reference constructors and scalar conversion.
#ifndef HAVOK_HKSIMDREAL_H
#define HAVOK_HKSIMDREAL_H
#include <vectorintrinsics.h>
#include "cd2/layout.h"
class hkSimdReal
{
public:
    hkSimdReal() {}
    hkSimdReal(const float &value) : m_real(__vspltw(__lvlx(&value, 0), 0)) {}
    hkSimdReal(const __vector4 &value) : m_real(value) {}
    operator float() const
    {
        float value;
        __stvewx(m_real, &value, 0);
        return value;
    }
    const __vector4 &getQuad() const { return m_real; }
private:
    __vector4 m_real;
    CD2_LAYOUT_CHECKS(hkSimdReal, CD2_SIZE(hkSimdReal, 0x10))
};
#endif
