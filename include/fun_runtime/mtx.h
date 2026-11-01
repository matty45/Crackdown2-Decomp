// Fun_Runtime::Mtx: STAND-IN for the 0x40-byte, 16-byte-aligned matrix in the reference headers.
// CD2 cBasePatrolRouteEvent's constructor (0x824BFA80) initializes three components of each
// 16-byte row to the identity transform; it leaves the fourth components untouched.
#ifndef FUN_RUNTIME_MTX_H
#define FUN_RUNTIME_MTX_H

#include "cd2/layout.h"

namespace Fun_Runtime
{
    __declspec(align(16)) class Mtx
    {
    public:
        float m_rows[4][4];

        Mtx()
        {
            m_rows[0][0] = 1.0f;
            m_rows[0][1] = 0.0f;
            m_rows[0][2] = 0.0f;
            m_rows[1][0] = 0.0f;
            m_rows[1][1] = 1.0f;
            m_rows[1][2] = 0.0f;
            m_rows[2][0] = 0.0f;
            m_rows[2][1] = 0.0f;
            m_rows[2][2] = 1.0f;
            m_rows[3][0] = 0.0f;
            m_rows[3][1] = 0.0f;
            m_rows[3][2] = 0.0f;
        }

        CD2_LAYOUT_CHECKS(Mtx,
            CD2_SIZE(Mtx, 0x40)
            CD2_OFFSET(Mtx, m_rows, 0))
    };
}

#endif
