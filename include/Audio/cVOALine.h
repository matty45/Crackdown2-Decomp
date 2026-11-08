#ifndef AUDIO_CVOALINE_H
#define AUDIO_CVOALINE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace Audio
{
    class cVOALine : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x83012B98);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cVOALineClass = new Fun_Runtime::cClass(0x678, "cVOALine", 0xF0);
            return *cVOALineClass;
        }
        static const Fun_Runtime::cClass *ms_pcVOALineClass;

        cVOALine();
        // Out of line (CD2 0x82835FE0): the deleting wrapper calls it.
        virtual ~cVOALine();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        unsigned char m_pad[0xF0 - 0x7C];
    };
}

#endif

