#ifndef AI_CCITYGLIDERMISSION_H
#define AI_CCITYGLIDERMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cCityGliderMission : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8E2E0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cCityGliderMissionClass = new Fun_Runtime::cClass(0xB4D8, "cCityGliderMission", 0x440);
            return *cCityGliderMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcCityGliderMissionClass;

        cCityGliderMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

