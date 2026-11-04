#ifndef Equip_cBulletData_H
#define Equip_cBulletData_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace Equip
{
    class cBulletData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82623EB8 (MakeNew calls it).
        cBulletData();

    private:
        unsigned char m_unmodelled18[0x138 - 0x18];

        CD2_LAYOUT_CHECKS(cBulletData, CD2_SIZE(cBulletData, 0x138))

    };
}

#endif
