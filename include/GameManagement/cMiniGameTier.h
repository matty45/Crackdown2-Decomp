#ifndef GameManagement_cMiniGameTier_H
#define GameManagement_cMiniGameTier_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cMiniGameTier : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
