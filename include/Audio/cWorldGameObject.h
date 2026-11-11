// Audio::cWorldGameObject (Crackdown 2): STAND-IN. MakeNew 0x82837608 and RetClassName 0x82837648
// (vtable slot 7 of 0x820022DC) from CD2's initializer run; RuffKing names the class in cWorldGameObject.obj.
// No layout or other virtuals are modelled yet.
#ifndef AUDIO_CWORLDGAMEOBJECT_H
#define AUDIO_CWORLDGAMEOBJECT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace Audio
{
    class cWorldGameObject
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // AUDIO_CWORLDGAMEOBJECT_H
