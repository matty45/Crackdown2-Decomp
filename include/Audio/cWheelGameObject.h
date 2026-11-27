// Audio::cWheelGameObject (Crackdown 2): STAND-IN. Name and base from RuffKing (Audio/cWheelGameObject.h; each
// Vehicle::tWheelInfo ends with one). CD2's wheel records are 0x120 bytes with this object at +0x68, so it is at most
// 0xB8 bytes; cLandVehicle's destructor (0x826C2458) stores only cGameObject's table into each, so its own destructor
// is compiler-generated. Nothing of its own is modelled.
#ifndef AUDIO_CWHEELGAMEOBJECT_H
#define AUDIO_CWHEELGAMEOBJECT_H

#include "Audio/cGameObject.h"

namespace Audio
{
    class cWheelGameObject : public cGameObject
    {
    private:
        unsigned char m_unmodelled90[0xB8 - 0x90];

        CD2_LAYOUT_CHECKS(cWheelGameObject,
            CD2_SIZE(cWheelGameObject, 0xB8))
    };
}

#endif // AUDIO_CWHEELGAMEOBJECT_H
