#ifndef Demo_cDemoSettings_H
#define Demo_cDemoSettings_H

#include "rws/attributes.h"

namespace Demo
{
    class cDemoSettings : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
