#ifndef CHARACTER_cCharacterProfile_H
#define CHARACTER_cCharacterProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace CHARACTER
{
    class cCharacterProfile : public RWS::CAttributeHandler
    {
    public:
        // CD2 0x82553650: attribute-handler vtable slot 5, returning Ret_OK.
        virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x825531E8 (MakeNew calls it).
        cCharacterProfile();

    private:
        unsigned char m_unmodelled18[0x260 - 0x18];

        CD2_LAYOUT_CHECKS(cCharacterProfile, CD2_SIZE(cCharacterProfile, 0x260))

    };
}

#endif
