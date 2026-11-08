#ifndef AUDIO_CWORLDGAMEOBJECTPOSITION_H
#define AUDIO_CWORLDGAMEOBJECTPOSITION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace Audio
{
    class cWorldGameObjectPosition : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x83013AD8);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cWorldGameObjectPositionClass = new Fun_Runtime::cClass(0x677, "cWorldGameObjectPosition", 0x50);
            return *cWorldGameObjectPositionClass;
        }
        static const Fun_Runtime::cClass *ms_pcWorldGameObjectPositionClass;

        cWorldGameObjectPosition();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

