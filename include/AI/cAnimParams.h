#ifndef AI_CANIMPARAMS_H
#define AI_CANIMPARAMS_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    class cAnimParams : public cNonGameBase
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F9EE10);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cAnimParamsClass = new Fun_Runtime::cClass(0x9F407, "cAnimParams", 0x48);
            return *cAnimParamsClass;
        }
        static const Fun_Runtime::cClass *ms_pcAnimParamsClass;

        cAnimParams();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
    };
}

#endif

