// TGT::cAiTargeting (Crackdown 2): STAND-IN, 0x60 bytes as in RuffKing. CD2's instances carry vptr 0x82147B98 and their
// owner at +4: CHARACTER::cCwCharacterWrapper's m_Targeting (0x2F40) and CHARACTER::cCwTransCharacterWrapper's
// m_AiTargeting (0x35C0). Not modelled beyond its size.
#ifndef TGT_CAITARGETING_H
#define TGT_CAITARGETING_H

#include "TGT/cTargeting.h"

namespace TGT
{
    class cAiTargeting : public cTargeting
    {
    private:
        unsigned char m_pad08[0x60 - 0x8];

    public:
        CD2_LAYOUT_CHECKS(cAiTargeting,
            CD2_SIZE(cAiTargeting, 0x60))
    };
}

#endif // TGT_CAITARGETING_H
