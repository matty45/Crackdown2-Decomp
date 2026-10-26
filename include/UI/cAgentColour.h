#ifndef UI_cAgentColour_H
#define UI_cAgentColour_H

#include "rws/attributes.h"

namespace UI
{
    class cAgentColour : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
