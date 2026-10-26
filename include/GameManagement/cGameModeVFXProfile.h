#ifndef GameManagement_cGameModeVFXProfile_H
#define GameManagement_cGameModeVFXProfile_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cGameModeVFXProfile : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
