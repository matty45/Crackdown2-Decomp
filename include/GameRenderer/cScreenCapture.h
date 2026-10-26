#ifndef GameRenderer_cScreenCapture_H
#define GameRenderer_cScreenCapture_H

#include "rws/attributes.h"

namespace GameRenderer
{
    class cScreenCapture : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
