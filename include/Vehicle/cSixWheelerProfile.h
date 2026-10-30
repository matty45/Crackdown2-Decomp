#ifndef Vehicle_cSixWheelerProfile_H
#define Vehicle_cSixWheelerProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cSixWheelerProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
