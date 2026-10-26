#ifndef Equip_cUVLightAttachmentData_H
#define Equip_cUVLightAttachmentData_H

#include "rws/attributes.h"

namespace Equip
{
    class cUVLightAttachmentData : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
