// Fun_Runtime::Mtx: STAND-IN for the 0x40-byte, 16-byte-aligned matrix in the reference headers.
// CD2 cBasePatrolRouteEvent's constructor (0x824BFA80) initializes three components of each
// 16-byte row to the identity transform; it leaves the fourth components untouched.
#ifndef FUN_RUNTIME_MTX_H
#define FUN_RUNTIME_MTX_H

#include "cd2/layout.h"
#include <ppcintrinsics.h>

namespace Fun_Runtime
{
    __declspec(align(16)) class Mtx
    {
    public:
        union
        {
            float m_rows[4][4];
            __vector4 m_vectorRows[4];
        };

        // RuffKing wraps an XMMATRIX. CD2 0x8284D870 copies all four vector rows,
        // including their fourth components, rather than rebuilding the transform.
        Mtx &operator=(const Mtx &other)
        {
            m_vectorRows[0] = other.m_vectorRows[0];
            m_vectorRows[1] = other.m_vectorRows[1];
            m_vectorRows[2] = other.m_vectorRows[2];
            m_vectorRows[3] = other.m_vectorRows[3];
            return *this;
        }

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
