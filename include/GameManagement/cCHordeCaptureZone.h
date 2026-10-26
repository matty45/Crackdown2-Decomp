#ifndef GameManagement_cCHordeCaptureZone_H
#define GameManagement_cCHordeCaptureZone_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeCaptureZone : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
