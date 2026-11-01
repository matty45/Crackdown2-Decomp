#ifndef Prop_cHingedDoor_H
#define Prop_cHingedDoor_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace Prop
{
    class cHingedDoor : public RWS::CAttributeHandler
    {
    public:
        static const Fun_Runtime::cClass *ms_pcHingedDoorClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    };
}

#endif
