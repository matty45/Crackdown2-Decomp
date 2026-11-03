// STAND-IN: RuffKing/Burn base order. CD2 constructor 0x824E00A8 initializes
// CAttributeHandler at 0, CEventHandler at 0x18, the event ID at 0x1C and two
// 12-byte sequence maps at 0x24. The constructor takes no packet in CD2.
#ifndef ANIM_CSPECIFICANIMATIONPROFILE_H
#define ANIM_CSPECIFICANIMATIONPROFILE_H

#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/eventid.h"
#include "fun_runtime/class.h"

namespace Anim
{
    class cSpecificAnimationProfile : public RWS::CAttributeHandler, public RWS::CEventHandler
    {
    public:
        cSpecificAnimationProfile();
        virtual ~cSpecificAnimationProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual void HandleEvents(RWS::CMsg &);
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
    protected:
        RWS::CEventId m_Msg_Return_Self;
    private:
        unsigned char m_unmodelledSequenceMaps[0x18];
        CD2_LAYOUT_CHECKS(cSpecificAnimationProfile,
            CD2_SIZE(cSpecificAnimationProfile, 0x3C)
            CD2_OFFSET(cSpecificAnimationProfile, m_Msg_Return_Self, 0x1C))
    };
}
#endif
