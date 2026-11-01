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
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcNetGameAISpawnPointClass;
        static Fun_Runtime::cClass &StaticCreateClass();
    };
}

#endif // UNKNOWN_CNETGAMEAISPAWNPOINT_H
