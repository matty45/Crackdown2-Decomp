#ifndef GangManager_cGangInfoPrototype_H
#define GangManager_cGangInfoPrototype_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace GangManager
{
    class cGangInfoPrototype : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82676E28 (MakeNew calls it).
        cGangInfoPrototype();

    private:
        unsigned char m_unmodelled18[0xD0 - 0x18];

        CD2_LAYOUT_CHECKS(cGangInfoPrototype, CD2_SIZE(cGangInfoPrototype, 0xD0))

    };
}

#endif
