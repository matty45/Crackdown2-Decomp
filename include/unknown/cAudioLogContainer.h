#include "rws/attributes.h"
// unknown::cAudioLogContainer (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FF1518) registers "cAudioLogContainer" with MakeNew (0x8270FC88) and size 0xC4.
#ifndef UNKNOWN_CAUDIOLOGCONTAINER_H
#define UNKNOWN_CAUDIOLOGCONTAINER_H

namespace unknown
{
    class cAudioLogContainer
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
    };
}

#endif // UNKNOWN_CAUDIOLOGCONTAINER_H
