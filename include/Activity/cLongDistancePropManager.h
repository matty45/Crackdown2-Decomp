#include "rws/attributes.h"
// Activity::cLongDistancePropManager (Crackdown 2): STAND-IN for the class name only. Base cNonGameBase, as in
// RuffKing's header; RetClassName (0x823DA878) is slot 11 of the vtable at 0x820FA250, as cNonGameBase's RetClassName.
#ifndef ACTIVITY_CLONGDISTANCEPROPMANAGER_H
#define ACTIVITY_CLONGDISTANCEPROPMANAGER_H

#include "gom/non_game_base.h"

namespace Activity
{
    class cLongDistancePropManager : public cNonGameBase
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 registered-class vtable 0x820FA378 slot 0, descriptor at 0x83802BF8.
        static const Fun_Runtime::cClass *ms_pcLongDistancePropManagerClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual const char *RetClassName() const;
    };
}

#endif // ACTIVITY_CLONGDISTANCEPROPMANAGER_H
