// hkMatrix3: Havok's 3x3 matrix, three column vectors (common/hkmath/linear/hkmatrix3.h). Layout from the RuffKing PDB.
#ifndef HAVOK_HKMATRIX3_H
#define HAVOK_HKMATRIX3_H

#include "Havok/hkVector4.h"

class hkMatrix3
{
public:
    hkMatrix3() {}

protected:
    hkVector4 m_col0;
    hkVector4 m_col1;
    hkVector4 m_col2;

    CD2_LAYOUT_CHECKS(hkMatrix3,
        CD2_SIZE(hkMatrix3, 0x30))
};

#endif // HAVOK_HKMATRIX3_H
