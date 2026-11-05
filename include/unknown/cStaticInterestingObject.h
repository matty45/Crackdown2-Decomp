#include "rws/attributes.h"
// unknown::cStaticInterestingObject: interface stand-in. Constructor 0x82455940
// calls cInterestingObject, then constructs CAttributeHandler at +0x40 and
// CEventHandler at +0x58. Instance fields remain incomplete; do not allocate this type.
// StaticCreateClass (0x824558A8) builds cClass(0x3EB, "cStaticInterestingObject", 0xC0); 0xC0 is the size its registrar gives.
#ifndef UNKNOWN_CSTATICINTERESTINGOBJECT_H
#define UNKNOWN_CSTATICINTERESTINGOBJECT_H

#include "fun_runtime/class.h"
#include "unknown/cInterestingObject.h"
#include "rws/eventhandler.h"

namespace unknown
{
    class cStaticInterestingObject : public cInterestingObject, public RWS::CAttributeHandler, public RWS::CEventHandler
    {
    public:
        // CD2 0x824556F8: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x82455708: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x824557B8: returns the class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcStaticInterestingObjectClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSTATICINTERESTINGOBJECT_H
