#ifndef AI_CHELICALLZONE_H
#define AI_CHELICALLZONE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cHeliCallZone : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8EEC0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cHeliCallZoneClass = new Fun_Runtime::cClass(0x85D0F, "cHeliCallZone", 0x1F0);
            return *cHeliCallZoneClass;
        }
        static const Fun_Runtime::cClass *ms_pcHeliCallZoneClass;

        cHeliCallZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

