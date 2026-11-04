#ifndef unknown_cCrowdManager_H
#define unknown_cCrowdManager_H

#include "cd2/layout.h"
#include "rws/attributes.h"

namespace unknown
{
    class cCrowdManager : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x825EC2F0 (MakeNew calls it).
        cCrowdManager();

    private:
        unsigned char m_unmodelled18[0x60 - 0x18];

        CD2_LAYOUT_CHECKS(cCrowdManager, CD2_SIZE(cCrowdManager, 0x60))

    };
}

#endif
