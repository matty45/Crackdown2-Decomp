// ZoneManager::cPlayerTriggerZone (Crackdown 2): STAND-IN. RuffKing base cPlayerTriggerBase, no fields (size 0xE0). Its
// destructor is inline and empty in CD2: the derived destructors (cTrainingTrigger's 0x82485720) restore this class's
// vtables (0x82155B98 at 0) before calling cPlayerTriggerBase's.
#ifndef ZONEMANAGER_CPLAYERTRIGGERZONE_H
#define ZONEMANAGER_CPLAYERTRIGGERZONE_H

#include "ZoneManager/cPlayerTriggerBase.h"

namespace ZoneManager
{
    class cPlayerTriggerZone : public cPlayerTriggerBase
    {
    public:
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool IsWithin(const Fun_Runtime::Vec3 &) const;
        // Inline in CD2: the zones' MakeNew functions call cPlayerTriggerBase's constructor directly.
        __forceinline cPlayerTriggerZone(bool bAllowDeadCharacters) : cPlayerTriggerBase(bAllowDeadCharacters) {}
        virtual ~cPlayerTriggerZone() {}

        CD2_LAYOUT_CHECKS(cPlayerTriggerZone, CD2_SIZE(cPlayerTriggerZone, 0xE0))
    };
}

#endif // ZONEMANAGER_CPLAYERTRIGGERZONE_H
