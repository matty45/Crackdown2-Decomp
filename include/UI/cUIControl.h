#ifndef UI_cUIControl_H
#define UI_cUIControl_H

#include "rws/attributes.h"

namespace UI
{
    class cUIControl : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
