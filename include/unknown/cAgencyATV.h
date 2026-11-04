#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cAgencyATV (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x826E3300) builds cClass(0x12065, "cAgencyATV", 0x31F0); 0x31F0 is the size its registrar gives.
#ifndef UNKNOWN_CAGENCYATV_H
#define UNKNOWN_CAGENCYATV_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cAgencyATV
    {
    public:
        // CD2 0x826E2300: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826E23C8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEAD28 names placement factory 0x826e23d8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyATVClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CAGENCYATV_H
