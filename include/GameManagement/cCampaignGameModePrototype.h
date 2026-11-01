#ifndef GameManagement_cCampaignGameModePrototype_H
#define GameManagement_cCampaignGameModePrototype_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCampaignGameModePrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
