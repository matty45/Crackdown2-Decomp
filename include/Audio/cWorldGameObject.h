// Audio::cWorldGameObject (Crackdown 2): STAND-IN for the class statics only (MakeNew 0x82837608, from its registrars in CD2's
// initializer run); RuffKing names the class in cWorldGameObject.obj. No layout or virtuals are modelled yet.
#ifndef AUDIO_CWORLDGAMEOBJECT_H
#define AUDIO_CWORLDGAMEOBJECT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace Audio
{
    class cWorldGameObject
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AUDIO_CWORLDGAMEOBJECT_H
