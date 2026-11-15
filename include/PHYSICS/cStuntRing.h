// PHYSICS::cStuntRing: STAND-IN, reference base order; CD2 factory and descriptor confirm size 0x1C0.
// Its own storage remains opaque, and no constructor or destructor body is reconstructed here.
#ifndef PHYSICS_CSTUNTRING_H
#define PHYSICS_CSTUNTRING_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"

namespace PHYSICS
{
    __declspec(align(16)) class cStuntRing : public RWS::CSystemCommands, public cNonGameBase
    {
    public:
        // CD2 0x82711CC0 is called out of line, without a packet.
        cStuntRing();
        virtual ~cStuntRing();
        virtual const char *RetClassName() const;
        // CD2 0x82711A60 / 0x82711A70: the registered-class pair, at the start of this object's code.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcStuntRingClass;
    private:
        // The reference owns aligned transform/box storage and an audio object in this region.
        unsigned char m_unmodelled7C[0x1C0 - 0x7C];
        CD2_LAYOUT_CHECKS(cStuntRing, CD2_SIZE(cStuntRing, 0x1C0))
    };
}

#endif // PHYSICS_CSTUNTRING_H
