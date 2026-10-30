#ifndef Vehicle_cHelicopter_H
#define Vehicle_cHelicopter_H

#include "rws/attributes.h"

namespace Vehicle
{
    class cHelicopter : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
