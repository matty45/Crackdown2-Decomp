#ifndef TGT_cPrecisionAimProfile_H
#define TGT_cPrecisionAimProfile_H

#include "rws/attributes.h"

namespace TGT
{
    class cPrecisionAimProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
