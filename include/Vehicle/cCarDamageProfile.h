#ifndef Vehicle_cCarDamageProfile_H
#define Vehicle_cCarDamageProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cCarDamageProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
