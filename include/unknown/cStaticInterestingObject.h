#include "rws/attributes.h"
// unknown::cStaticInterestingObject (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x824558A8) builds cClass(0x3EB, "cStaticInterestingObject", 0xC0); 0xC0 is the size its registrar gives.
#ifndef UNKNOWN_CSTATICINTERESTINGOBJECT_H
#define UNKNOWN_CSTATICINTERESTINGOBJECT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cStaticInterestingObject
    {
    public:
        // CD2 0x82455708: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcStaticInterestingObjectClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSTATICINTERESTINGOBJECT_H
