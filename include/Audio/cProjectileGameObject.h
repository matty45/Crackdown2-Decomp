// Audio::cProjectileGameObject (Crackdown 2): STAND-IN. Name and base from RuffKing (cHWProjectile::m_ProjectileAudio,
// Audio/cProjectileGameObject.h). CD2's cHWProjectile embeds one at 0x8C8, 0xA8 bytes up to the class's end (0x970).
// Its destructor is expanded in cHWProjectile's (0x8262AAF8): when registered (+8 not -1) it posts an event, sets two
// values to 0 and unregisters, then calls ~cGameObject (0x8237A748). That body is not modelled: the destructor is
// declared here only.
#ifndef AUDIO_CPROJECTILEGAMEOBJECT_H
#define AUDIO_CPROJECTILEGAMEOBJECT_H

#include "Audio/cGameObject.h"

namespace Audio
{
    class cProjectileGameObject : public cGameObject
    {
    public:
        virtual ~cProjectileGameObject();

    private:
        unsigned char m_unmodelledC[0xA8 - 0xC];

        CD2_LAYOUT_CHECKS(cProjectileGameObject,
            CD2_SIZE(cProjectileGameObject, 0xA8))
    };
}

#endif // AUDIO_CPROJECTILEGAMEOBJECT_H
