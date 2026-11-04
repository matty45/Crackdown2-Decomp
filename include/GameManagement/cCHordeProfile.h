#ifndef GameManagement_cCHordeProfile_H
#define GameManagement_cCHordeProfile_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GameManagement
{
    class cCHordeProfile : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82865378 (MakeNew calls it).
        cCHordeProfile();

    private:
        unsigned char m_unmodelled18[0xD8 - 0x18];

        CD2_LAYOUT_CHECKS(cCHordeProfile, CD2_SIZE(cCHordeProfile, 0xD8))

    };
}

#endif
