#ifndef GameManagement_cCHordeCaptureProfile_H
#define GameManagement_cCHordeCaptureProfile_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeCaptureProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
