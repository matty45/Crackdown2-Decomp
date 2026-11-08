// Activity::cCampaignWeaponSpawnPoint (Crackdown 2): STAND-IN for the class statics only (StaticCreateClass 0x823D0270, MakeNew 0x823D0310, from its registrars in CD2's
// initializer run); RuffKing names the class in cCampaignWeaponSpawnPoint.obj. No layout or virtuals are modelled yet;
// base Activity::cSpawnPointBase from CD2's inheritance registrar.
#ifndef ACTIVITY_CCAMPAIGNWEAPONSPAWNPOINT_H
#define ACTIVITY_CCAMPAIGNWEAPONSPAWNPOINT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "Activity/cSpawnPointBase.h"

namespace Activity
{
    class cCampaignWeaponSpawnPoint : public cSpawnPointBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCampaignWeaponSpawnPointClass;
    };
}

#endif // ACTIVITY_CCAMPAIGNWEAPONSPAWNPOINT_H
