#ifndef AI_CANIMPARAMS_H
#define AI_CANIMPARAMS_H

#include "rws/attributes.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    // CD2's table (0x8210F6EC) has RWS::CAttributeHandler's eleven slots, then RetClass, IsA, RetClassName and Destruct in slots
    // 11 to 14, as RuffKing and Burn declares the class: a CAttributeHandler.
    class cAnimParams : public RWS::CAttributeHandler
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
        virtual void Destruct();
        // CD2: cAnimParams's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x824DF750
    };
}

#endif

