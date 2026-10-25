// TGT::cPlayerTargeting (Crackdown 2): STAND-IN, sized to CD2. 0x7C0 bytes in CD2 (0x7B0 in RuffKing): it is the member
// CHARACTER::cCwTransCharacterWrapper::m_Targeting at 0x2E00, and the next member starts at 0x35C0. Its constructor is
// 0x827790F0 (called with the member and its owner). Not modelled beyond its size.
#ifndef TGT_CPLAYERTARGETING_H
#define TGT_CPLAYERTARGETING_H

#include "TGT/cTargeting.h"

namespace TGT
{
    class cPlayerTargeting : public cTargeting
    {
    private:
        unsigned char m_pad08[0x7C0 - 0x8];

    public:
        CD2_LAYOUT_CHECKS(cPlayerTargeting,
            CD2_SIZE(cPlayerTargeting, 0x7C0))
    };
}

#endif // TGT_CPLAYERTARGETING_H
