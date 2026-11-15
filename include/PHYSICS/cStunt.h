// PHYSICS::cStunt: STAND-IN, reference base order; CD2 factory/descriptor give size 0xEC.
// Own storage is opaque until individual members are recovered.
#ifndef PHYSICS_CSTUNT_H
#define PHYSICS_CSTUNT_H

#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"

namespace PHYSICS
{
    class cStunt : public RWS::CSystemCommands, public cNonGameBase
    {
    public:
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcStuntClass;
    private:
        unsigned char m_unmodelled7C[0xEC - 0x7C];
        CD2_LAYOUT_CHECKS(cStunt, CD2_SIZE(cStunt, 0xEC))
    };
}

#endif // PHYSICS_CSTUNT_H
