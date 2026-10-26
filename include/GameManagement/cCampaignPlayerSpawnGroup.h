#ifndef GameManagement_cCampaignPlayerSpawnGroup_H
#define GameManagement_cCampaignPlayerSpawnGroup_H

#include "rws/attributes.h"

namespace GameManagement
{
    class cCampaignPlayerSpawnGroup : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
    };
}

#endif
