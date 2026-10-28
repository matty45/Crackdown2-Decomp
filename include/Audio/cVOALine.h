#ifndef AUDIO_CVOALINE_H
#define AUDIO_CVOALINE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace Audio
{
    class cVOALine : public cNonGameBase
    {
    public:
        static const Fun_Runtime::cClass *ms_pcVOALineClass;

        cVOALine();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        unsigned char m_pad[0xF0 - 0x7C];
    };
}

#endif

