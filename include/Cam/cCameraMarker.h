#ifndef Cam_cCameraMarker_H
#define Cam_cCameraMarker_H

#include "rws/attributes.h"

namespace Cam
{
    class cCameraMarker : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
