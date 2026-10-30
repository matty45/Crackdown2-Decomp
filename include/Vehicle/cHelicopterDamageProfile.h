#ifndef Vehicle_cHelicopterDamageProfile_H
#define Vehicle_cHelicopterDamageProfile_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cHelicopterDamageProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
