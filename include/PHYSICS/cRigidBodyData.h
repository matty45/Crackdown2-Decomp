// PHYSICS::cRigidBodyData: STAND-IN, RuffKing name and base position (first base of cRigidBodyProfile). Only its
// virtual destructor is modelled: CD2's cRigidBodyProfile destructor (0x826A4368) ends with this class's inline
// destructor restoring its one-slot table, which the linker folded into cLinkedListItem's (0x820F9A84). The profile
// places cNonGameBase at 0x260, so this class is 0x260 bytes in CD2 (RuffKing's is 0x160); its fields (RuffKing:
// construct info at 0x10, camera settings) are not modelled.
#ifndef PHYSICS_CRIGIDBODYDATA_H
#define PHYSICS_CRIGIDBODYDATA_H

#include "cd2/layout.h"

namespace PHYSICS
{
    class cRigidBodyData
    {
    public:
        virtual ~cRigidBodyData() {}

    private:
        unsigned char m_unmodelled04[0x260 - 4];

        CD2_LAYOUT_CHECKS(cRigidBodyData, CD2_SIZE(cRigidBodyData, 0x260))
    };
}

#endif // PHYSICS_CRIGIDBODYDATA_H
