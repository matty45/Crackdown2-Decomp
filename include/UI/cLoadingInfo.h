#ifndef UI_cLoadingInfo_H
#define UI_cLoadingInfo_H

#include "rws/attributes.h"

namespace UI
{
    class cLoadingInfo : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
