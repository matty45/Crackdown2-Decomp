#include "rws/attributes.h"
// unknown::cScriptManager (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x82770218) builds cClass(0x60B, "cScriptManager", 0x430); 0x430 is the size its registrar gives.
#ifndef UNKNOWN_CSCRIPTMANAGER_H
#define UNKNOWN_CSCRIPTMANAGER_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cScriptManager
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcScriptManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CSCRIPTMANAGER_H
