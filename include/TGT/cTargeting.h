// TGT::cTargeting (Crackdown 2): STAND-IN. The base of the targeting classes a character points at through
// CHARACTER::cCharacter::m_pTargeting. Layout from RuffKing (8 bytes: the vptr, then m_pOwner); its vtable (over 40
// slots in RuffKing) is not modelled yet: Slot0 only gives the class its vptr.
#ifndef TGT_CTARGETING_H
#define TGT_CTARGETING_H

#include "cd2/layout.h"

namespace CHARACTER { class cCharacter; }

namespace TGT
{
    class cTargeting
    {
    public:
        virtual void Slot0();
    protected:
        CHARACTER::cCharacter *m_pOwner;

    public:
        CD2_LAYOUT_CHECKS(cTargeting,
            CD2_SIZE(cTargeting, 0x8)
            CD2_OFFSET(cTargeting, m_pOwner, 0x4))
    };
}

#endif // TGT_CTARGETING_H
