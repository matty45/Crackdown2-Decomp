#ifndef AUDIO_CWORLDGAMEOBJECTPOSITION_H
#define AUDIO_CWORLDGAMEOBJECTPOSITION_H

#include "rws/attributes.h"
#include "rws/systemcommands.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/memory.h"

namespace Audio
{
    // CD2's table (0x8215A508) has RWS::CAttributeHandler's eleven slots, then RetClass, IsA, RetClassName and Destruct in slots
    // 11 to 14, as Burn declares the class: a CAttributeHandler and RWS::CSystemCommands (RuffKing adds RWS::DynamicAllocationPolicy).
    class cWorldGameObjectPosition : public RWS::CAttributeHandler, public RWS::CSystemCommands
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
        virtual void Destruct();
        // CD2: cWorldGameObjectPosition's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x82838028
    };
}

#endif

