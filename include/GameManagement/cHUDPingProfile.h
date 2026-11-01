#ifndef GameManagement_cHUDPingProfile_H
#define GameManagement_cHUDPingProfile_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cHUDPingProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
