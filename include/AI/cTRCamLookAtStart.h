// STAND-IN: RuffKing's class/base/member names. CD2 descriptor at 0x824873B0
// gives size 0xC0; constructor 0x82487458 initializes the camera parameters
// at +0x90 after cBasePatrolRouteEvent construction through cTrainingRouteEvent.
#ifndef AI_CTRCAMLOOKATSTART_H
#define AI_CTRCAMLOOKATSTART_H
#include "AI/cTrainingRouteEvent.h"
#include "AI/tTCamCutParams.h"
namespace AI
{
    class cTRCamLookAtStart : public cTrainingRouteEvent
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcTRCamLookAtStartClass;
        cTRCamLookAtStart();
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    private:
        tTCamCutParams m_tCamParams;
        CD2_LAYOUT_CHECKS(cTRCamLookAtStart,
            CD2_SIZE(cTRCamLookAtStart, 0xC0)
            CD2_OFFSET(cTRCamLookAtStart, m_tCamParams, 0x90))
    };
}
#endif
