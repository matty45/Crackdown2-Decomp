#ifndef Vehicle_cCarDamageProfile_H
#define Vehicle_cCarDamageProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace Vehicle
{
    class cCarDamageProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x826A5648 (MakeNew calls it).
        cCarDamageProfile();

    private:
        unsigned char m_unmodelled18[0x230 - 0x18];

        CD2_LAYOUT_CHECKS(cCarDamageProfile, CD2_SIZE(cCarDamageProfile, 0x230))

    };
}

#endif
