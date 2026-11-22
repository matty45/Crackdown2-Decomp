// Equip::cLightAttachment (Crackdown 2): STAND-IN; names, members and virtual order from RuffKing's
// Equipment/Attachments/cLightAttachment.h. CD2's table 0x821227F0 has RuffKing's seven slots: the deleting
// destructor 0x82615718 only restores this table before freeing (an inline empty destructor), Init 0x82615760
// stores the owner at 0x14 and the data at 0x64 and copies the data's power time into 0x60, Term 0x82615808
// releases the light at 0x10, and CanActivate 0x82615820 tests the power time and the data's infinite-power flag.
#ifndef EQUIP_CLIGHTATTACHMENT_H
#define EQUIP_CLIGHTATTACHMENT_H

#include "cd2/layout.h"
#include "fun_runtime/mtx.h"
#include "GameRenderer/cFrame.h"
#include "VFX/cGlobalLight.h"

class cGameBase;

namespace Equip
{
    class cLightAttachmentData;

    class cLightAttachment
    {
    public:
        cLightAttachment();
        virtual ~cLightAttachment() {}
        virtual void Init(cGameBase *pOwner, cLightAttachmentData *pLightData);
        virtual void Term();
        virtual bool CanActivate() const;
        virtual bool Activate();
        virtual bool Deactivate();
        virtual void TickUpdate(float dT);
        // RuffKing's (out of line there, 0x82AFB868); CD2's cCWFirearm::ToggleLightAttachment and
        // IsLightAttachmentActive (0x82618118, 0x826181C8) expand it.
        bool IsActive() const { return m_pGlobalLight ? m_pGlobalLight->IsOn() : false; }

    protected:
        VFX::cGlobalLight *m_pGlobalLight;
        cGameBase *m_pOwner;
        cFrame m_AttachFrame;
        Fun_Runtime::Mtx m_RelativeTransform;
        float m_fCurrentPowerTime;
        cLightAttachmentData *m_pLightAttachmentData;

        CD2_LAYOUT_CHECKS(cLightAttachment,
            CD2_SIZE(cLightAttachment, 0x70)
            CD2_OFFSET(cLightAttachment, m_pGlobalLight, 0x10)
            CD2_OFFSET(cLightAttachment, m_pOwner, 0x14)
            CD2_OFFSET(cLightAttachment, m_AttachFrame, 0x18)
            CD2_OFFSET(cLightAttachment, m_RelativeTransform, 0x20)
            CD2_OFFSET(cLightAttachment, m_fCurrentPowerTime, 0x60)
            CD2_OFFSET(cLightAttachment, m_pLightAttachmentData, 0x64))
    };
}

#endif // EQUIP_CLIGHTATTACHMENT_H
