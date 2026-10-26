#ifndef GameManagement_cCHordeWave_H
#define GameManagement_cCHordeWave_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeWave : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
