#ifndef GameRenderer_cScreenCapture_H
#define GameRenderer_cScreenCapture_H

#include "rws/attributes.h"

namespace GameRenderer
{
    class cScreenCapture : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
