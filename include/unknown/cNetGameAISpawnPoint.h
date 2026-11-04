#include "rws/attributes.h"
// unknown::cNetGameAISpawnPoint (Crackdown 2): STAND-IN with only its runtime class descriptor; its bases are not modelled yet.
// StaticCreateClass (0x8284D068) builds cClass(0x4884, "cNetGameAISpawnPoint", 0xA0); 0xA0 is the size its registrar gives.
#ifndef UNKNOWN_CNETGAMEAISPAWNPOINT_H
#define UNKNOWN_CNETGAMEAISPAWNPOINT_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cNetGameAISpawnPoint
    {
    public:
        // CD2 0x8284D058: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcNetGameAISpawnPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CNETGAMEAISPAWNPOINT_H
