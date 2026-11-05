#ifndef VFX_cLightData_H
#define VFX_cLightData_H

#include "cd2/layout.h"
#include "rws/attributes.h"
#include "fun_runtime/string.h"

namespace VFX
{
    class cLightData : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
    public:
        // Out of line: CD2 0x82800828 (MakeNew calls it).
        cLightData();
        // CD2 0x82800768, called by the deleting wrapper 0x828007D8; it frees m_sName.
        virtual ~cLightData();

    private:
        Fun_Runtime::cString m_sName;                 // 0x18 (RuffKing name and type)
        unsigned char m_unmodelled34[0x1A0 - 0x34];

        CD2_LAYOUT_CHECKS(cLightData,
            CD2_SIZE(cLightData, 0x1A0)
            CD2_OFFSET(cLightData, m_sName, 0x18))

    };
}

#endif
