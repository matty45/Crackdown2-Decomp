#ifndef GameManagement_cCampaignPlayerSpawnPoint_H
#define GameManagement_cCampaignPlayerSpawnPoint_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCampaignPlayerSpawnPoint : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
