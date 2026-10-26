#ifndef unknown_cRenegadesProfile_H
#define unknown_cRenegadesProfile_H

#include "rws/attributes.h"

namespace unknown
{
    class cRenegadesProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
