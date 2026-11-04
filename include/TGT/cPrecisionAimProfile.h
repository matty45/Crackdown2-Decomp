#ifndef TGT_cPrecisionAimProfile_H
#define TGT_cPrecisionAimProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace TGT
{
    class cPrecisionAimProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x8277D258 (MakeNew calls it).
        cPrecisionAimProfile();

        CD2_LAYOUT_CHECKS(cPrecisionAimProfile, CD2_SIZE(cPrecisionAimProfile, 0x18))

    };
}

#endif
