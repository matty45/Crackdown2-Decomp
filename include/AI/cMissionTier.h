#ifndef AI_CMISSIONTIER_H
#define AI_CMISSIONTIER_H

#include "rws/attributes.h"
#include "rws/dynamicallocationpolicy.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace AI
{
    // CD2's table (0x82105BB4) has RWS::CAttributeHandler's eleven slots, then RetClass, IsA, RetClassName and Destruct in slots
    // 11 to 14, as RuffKing declares the class: a CAttributeHandler with RWS::DynamicAllocationPolicy.
    class cMissionTier : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        static __forceinline Fun_Runtime::cClass &StaticCreateClass()
        {
            // CD2 inlines the local-static guard and descriptor creation into the global initializer (0x82F901B8);
            // /Ob1 declines a plain inline function here, and CD2 keeps no separate copy.
            static Fun_Runtime::cClass *cMissionTierClass = new Fun_Runtime::cClass(0x40B, "cMissionTier", 0x64);
            return *cMissionTierClass;
        }
        static const Fun_Runtime::cClass *ms_pcMissionTierClass;

        cMissionTier();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // CD2: cMissionTier's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8248E620
    };
}

#endif

