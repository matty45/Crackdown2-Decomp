#ifndef VFX_cTracers_H
#define VFX_cTracers_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/class.h"

namespace VFX
{
    class cTracers : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcTracersClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x827B9A20 (MakeNew calls it).
        cTracers();

    private:
        unsigned char m_unmodelled18[0x138 - 0x18];

        CD2_LAYOUT_CHECKS(cTracers, CD2_SIZE(cTracers, 0x138))

    };
}

#endif
