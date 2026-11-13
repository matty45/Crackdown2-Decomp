// ZoneManager::cPlayerTriggerCylinder (Crackdown 2): STAND-IN. RuffKing base cPlayerTriggerBase and the three fields below
// (same offsets in CD2: cMissionActivationCylinder's handler follows at 0xF0). Its destructor is inline and empty in
// CD2: cMissionActivationCylinder's (0x8248B058) restores this class's vtables before calling cPlayerTriggerBase's.
#ifndef ZONEMANAGER_CPLAYERTRIGGERCYLINDER_H
#define ZONEMANAGER_CPLAYERTRIGGERCYLINDER_H

#include "ZoneManager/cPlayerTriggerBase.h"

namespace ZoneManager
{
    class cPlayerTriggerCylinder : public cPlayerTriggerBase
    {
    public:
        // CD2 0x8280E1E0, called without arguments by the updraft-zone factory.
        cPlayerTriggerCylinder();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool IsWithin(const Fun_Runtime::Vec3 &) const;
        virtual ~cPlayerTriggerCylinder() {}

    protected:
        float m_fHeight;
        float m_fRadius;
        float m_fRadiusSq;

        // CD2: cPlayerTriggerCylinder's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        // 13: 0x821D1D20
        // This is inherited cPlayerTriggerBase::IsVehicleWithin: both CD2 tables
        // hold the same address, and RuffKing's cylinder declares no override.
    protected:
        CD2_LAYOUT_CHECKS(cPlayerTriggerCylinder,
            CD2_SIZE(cPlayerTriggerCylinder, 0xF0)
            CD2_OFFSET(cPlayerTriggerCylinder, m_fHeight, 0xE0)
            CD2_OFFSET(cPlayerTriggerCylinder, m_fRadius, 0xE4)
            CD2_OFFSET(cPlayerTriggerCylinder, m_fRadiusSq, 0xE8))
    };
}

#endif // ZONEMANAGER_CPLAYERTRIGGERCYLINDER_H
