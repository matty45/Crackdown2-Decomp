#ifndef Equip_cLightAttachmentData_H
#define Equip_cLightAttachmentData_H

#include "rws/attributes.h"

namespace Equip
{
    class cLightAttachmentData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
