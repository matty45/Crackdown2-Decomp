#ifndef Prop_cHingedDoor_H
#define Prop_cHingedDoor_H

#include "rws/attributes.h"

namespace Prop
{
    class cHingedDoor : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
