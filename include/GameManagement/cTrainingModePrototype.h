#ifndef GameManagement_cTrainingModePrototype_H
#define GameManagement_cTrainingModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cTrainingModePrototype : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
