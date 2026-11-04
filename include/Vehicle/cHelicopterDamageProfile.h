#ifndef Vehicle_cHelicopterDamageProfile_H
#define Vehicle_cHelicopterDamageProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace Vehicle
{
    class cHelicopterDamageProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x826C0730 (MakeNew calls it).
        cHelicopterDamageProfile();

    private:
        unsigned char m_unmodelled18[0x110 - 0x18];

        CD2_LAYOUT_CHECKS(cHelicopterDamageProfile, CD2_SIZE(cHelicopterDamageProfile, 0x110))

    };
}

#endif
