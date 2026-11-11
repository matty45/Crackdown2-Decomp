// STAND-IN: Havok array storage from the reference declarations. Used only as embedded storage here.
#ifndef HAVOK_HKARRAY_H
#define HAVOK_HKARRAY_H
#include "cd2/layout.h"
template <class T> class hkArray
{
public:
    T *m_data;
    int m_size;
    int m_capacityAndFlags;
    CD2_LAYOUT_CHECKS(hkArray, CD2_SIZE(hkArray, 12))
};
#endif
