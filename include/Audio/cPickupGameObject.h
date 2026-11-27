// Audio::cPickupGameObject (Crackdown 2): STAND-IN. Name, base and m_eLoop from RuffKing (Audio/cPickupGameObject.h;
// cRenegadeOrb::m_RenegadeOrbAudio). CD2's table 0x82001404 differs from cGameObject's (0x8215982C) only in the
// deleting destructor (0x828328A0) and RetType (0x8288BDB0). cRenegadeOrb's constructor (0x827570B0) expands this
// class's: after cGameObject's fields it stores 0x40 at +0x90 (m_eLoop), and the orb's next member follows at +0x98.
// The destructor is inline: the deleting destructor and the orb's (0x82757240) store the table and call ~cGameObject.
#ifndef AUDIO_CPICKUPGAMEOBJECT_H
#define AUDIO_CPICKUPGAMEOBJECT_H

#include "Audio/cGameObject.h"

namespace Audio
{
    class cPickupGameObject : public cGameObject
    {
    public:
        virtual ~cPickupGameObject() {}
        virtual eGameObjectType RetType() const;

    private:
        int m_eLoop;    // RuffKing's eLoopingEvent

        CD2_LAYOUT_CHECKS(cPickupGameObject,
            CD2_OFFSET(cPickupGameObject, m_eLoop, 0x90)
            CD2_SIZE(cPickupGameObject, 0x98))
    };
}

#endif // AUDIO_CPICKUPGAMEOBJECT_H
