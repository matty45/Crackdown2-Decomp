#include "cd2/layout.h"
#include "fun_runtime/class.h"
#ifndef CHARACTER_cCwCharacter_H
#define CHARACTER_cCwCharacter_H

#include "rws/attributes.h"

namespace CHARACTER
{
    class cCwCharacter : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x8253F4D8 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82540068 (MakeNew calls it with the packet).
        cCwCharacter(const RWS::CAttributePacket &packet);

    private:
        unsigned char m_unmodelled18[0x340 - 0x18];

        CD2_LAYOUT_CHECKS(cCwCharacter, CD2_SIZE(cCwCharacter, 0x340))

    };
}

#endif
