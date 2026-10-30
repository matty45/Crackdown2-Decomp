#ifndef unknown_cAgencyGarageDoor_H
#define unknown_cAgencyGarageDoor_H

#include "rws/attributes.h"

namespace unknown
{
    class cAgencyGarageDoor : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
