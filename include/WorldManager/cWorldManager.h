#ifndef WorldManager_cWorldManager_H
#define WorldManager_cWorldManager_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace WorldManager
{
    class cWorldManager : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcWorldManagerClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82278B80 (MakeNew calls it).
        cWorldManager();

    private:
        unsigned char m_unmodelled18[0x5DA0 - 0x18];

        CD2_LAYOUT_CHECKS(cWorldManager, CD2_SIZE(cWorldManager, 0x5DA0))

    };
}

#endif
