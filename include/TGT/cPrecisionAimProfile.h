#ifndef TGT_cPrecisionAimProfile_H
#define TGT_cPrecisionAimProfile_H

#include "rws/attributes.h"

namespace TGT
{
    class cPrecisionAimProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
