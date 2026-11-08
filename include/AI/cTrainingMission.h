#ifndef AI_CTRAININGMISSION_H
#define AI_CTRAININGMISSION_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cTrainingMission : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F8BBD0);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cTrainingMissionClass = new Fun_Runtime::cClass(0xB4D6, "cTrainingMission", 0x9D0);
            return *cTrainingMissionClass;
        }
        static const Fun_Runtime::cClass *ms_pcTrainingMissionClass;

        cTrainingMission();
        // The body (0x82206500) lies in the order-list region; its deleting wrapper (0x8247F3F8) calls it.
        virtual ~cTrainingMission();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

