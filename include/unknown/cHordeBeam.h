#ifndef unknown_cHordeBeam_H
#define unknown_cHordeBeam_H

#include "rws/attributes.h"

namespace unknown
{
    class cHordeBeam : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
