// Reference name, base and trigger enum. CD2 0x825012F8 resets +0x1C
// before calling cBaseActionData::ResetData; table 0x821150D8 owns slot 1.
#pragma once
#include "CHARACTER/cBaseActionData.h"
namespace CHARACTER
{
    enum eLedgeTriggers
    {
        eLedgeT_None = 0
    };
    class cActionDataLedge : public cBaseActionData
    {
    public:
        cActionDataLedge();
        virtual ~cActionDataLedge();
        virtual void ResetData();
        eLedgeTriggers m_eTriggers;

        CD2_LAYOUT_CHECKS(cActionDataLedge,
            CD2_SIZE(cActionDataLedge, 0x20)
            CD2_OFFSET(cActionDataLedge, m_eTriggers, 0x1C))
    };
}
