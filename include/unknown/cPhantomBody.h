#include "rws/attributes.h"
// unknown::cPhantomBody (Crackdown 2): STAND-IN. Base cGameBase (its inheritance registrar); fields not modelled.
// StaticCreateClass (0x8268A408) builds cClass(0x7, "cPhantomBody", 0x140); 0x140 is the size its registrar gives.
#ifndef UNKNOWN_CPHANTOMBODY_H
#define UNKNOWN_CPHANTOMBODY_H

#include "fun_runtime/class.h"
#include "gom/game_base.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace unknown
{
    class cPhantomBody : public cGameBase
    {
    public:
        virtual const char *RetClassName() const;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcPhantomBodyClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // Out of line: CD2 0x8268A4A0 (SpawnFromPrototype tail-calls it).
        cPhantomBody();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);

    private:
        unsigned char m_unmodelled120[0x140 - 0x120];

        CD2_LAYOUT_CHECKS(cPhantomBody, CD2_SIZE(cPhantomBody, 0x140))
    };
}

#endif // UNKNOWN_CPHANTOMBODY_H
