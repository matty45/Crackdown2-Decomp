#ifndef Equip_cBulletData_H
#define Equip_cBulletData_H

#include "rws/attributes.h"

namespace Equip
{
    class cBulletData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
