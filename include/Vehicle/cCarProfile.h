#ifndef Vehicle_cCarProfile_H
#define Vehicle_cCarProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cCarProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
