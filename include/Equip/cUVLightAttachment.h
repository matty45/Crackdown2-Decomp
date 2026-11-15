// Equip::cUVLightAttachment (Crackdown 2): STAND-IN; names from RuffKing's Equipment/Attachments/cUVLightAttachment.h,
// where its destructor is compiler-generated. CD2's table 0x821231B8 differs from cLightAttachment's only at Init
// (slot 1) and TickUpdate (slot 6); its slot 0 is cLightAttachment's deleting destructor 0x82615718 (identical
// bodies folded). cCWFirearm embeds one at 0xA40.
#ifndef EQUIP_CUVLIGHTATTACHMENT_H
#define EQUIP_CUVLIGHTATTACHMENT_H

#include "Equip/cLightAttachment.h"

namespace Equip
{
    class cUVLightAttachment : public cLightAttachment
    {
    public:
        typedef cLightAttachment cSuper;
        virtual void Init(cGameBase *pOwner, cLightAttachmentData *pLightData);
        virtual void TickUpdate(float dT);
        void DoUVLightDamage();

        CD2_LAYOUT_CHECKS(cUVLightAttachment, CD2_SIZE(cUVLightAttachment, 0x70))
    };
}

#endif // EQUIP_CUVLIGHTATTACHMENT_H
