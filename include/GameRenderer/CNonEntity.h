#ifndef GameRenderer_CNonEntity_H
#define GameRenderer_CNonEntity_H

#include "rws/attributes.h"

namespace GameRenderer
{
    class CNonEntity : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
