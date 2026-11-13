// STAND-IN: RuffKing Physics/cOBBox.h supplies these member names and methods.
// CD2 cPlayerTriggerZone::IsWithin (0x8280E1D8) passes its box at +0x30 to
// IsPenetratingPoint (0x8230F908); that body reads the transform at +0x10.
#ifndef PHYSICS_COBBOX_H
#define PHYSICS_COBBOX_H

#include "fun_runtime/vec3.h"
#include "fun_runtime/mtx.h"
#include "cd2/layout.h"

namespace PHYSICS
{
    class cOBBox
    {
    public:
        cOBBox();
        cOBBox(const Fun_Runtime::Mtx &, const Fun_Runtime::Vec3 &);
        void SetTransform(const Fun_Runtime::Mtx &);
        void SetScale(const Fun_Runtime::Vec3 &);
        bool IsPenetratingPoint(const Fun_Runtime::Vec3 &) const;
        bool IsPenetratingSphere(const Fun_Runtime::Vec3 &, float) const;
        bool IsPenetratingOBB(const cOBBox &) const;

        Fun_Runtime::Vec3 m_vecScale;
        Fun_Runtime::Mtx m_mtxTrans;

        CD2_LAYOUT_CHECKS(cOBBox,
            CD2_SIZE(cOBBox, 0x50)
            CD2_OFFSET(cOBBox, m_vecScale, 0)
            CD2_OFFSET(cOBBox, m_mtxTrans, 0x10))
    };
}

#endif
