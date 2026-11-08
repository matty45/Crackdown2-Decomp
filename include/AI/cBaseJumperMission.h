#ifndef AI_CBASEJUMPERMISSION_H
#define AI_CBASEJUMPERMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cBaseJumperMission : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8DDC0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cBaseJumperMissionClass = new Fun_Runtime::cClass(0xB4D9, "cBaseJumperMission", 0x400);
            return *cBaseJumperMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcBaseJumperMissionClass;

        cBaseJumperMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

