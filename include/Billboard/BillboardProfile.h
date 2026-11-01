#ifndef Billboard_BillboardProfile_H
#define Billboard_BillboardProfile_H

#include "rws/attributes.h"

namespace Billboard
{
    class BillboardProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
