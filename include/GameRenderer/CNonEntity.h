#ifndef GameRenderer_CNonEntity_H
#define GameRenderer_CNonEntity_H

#include "rws/attributes.h"
#include "cd2/layout.h"

namespace GameRenderer
{
    class CNonEntity : public RWS::CAttributeHandler
    {
    public:
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);

    private:
        unsigned char m_pad[0x1c - 0x18];

        CD2_LAYOUT_CHECKS(CNonEntity,
            CD2_SIZE(CNonEntity, 0x1c))
    };
}

#endif
