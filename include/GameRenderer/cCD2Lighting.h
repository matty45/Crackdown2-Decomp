#ifndef GameRenderer_cCD2Lighting_H
#define GameRenderer_cCD2Lighting_H

#include "rws/attributes.h"

namespace GameRenderer
{
    class cCD2Lighting : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
