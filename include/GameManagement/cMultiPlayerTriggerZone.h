#ifndef GameManagement_cMultiPlayerTriggerZone_H
#define GameManagement_cMultiPlayerTriggerZone_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cMultiPlayerTriggerZone : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
