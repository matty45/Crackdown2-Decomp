#ifndef Vehicle_cGenericCarDamageProfile_H
#define Vehicle_cGenericCarDamageProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cGenericCarDamageProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
