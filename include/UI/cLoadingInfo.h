#ifndef UI_cLoadingInfo_H
#define UI_cLoadingInfo_H

#include "rws/attributes.h"
#include "fun_runtime/stringc.h"

namespace UI
{
    class cLoadingInfo : public RWS::CAttributeHandler
    {
        // Names through m_ImageFile are from RuffKing ScreenLoading.h; CD2's
        // factory 0x828B09A8 verifies these offsets. The final fields are CD2-only.
        unsigned int m_NameHash[4];
        float m_ExtraDisplayTime;
        Fun_Runtime::cStringc m_ImageFile;
        int m_nGroup; // destructor selects one of two lists using this field
        unsigned int m_word4C;
        bool m_bDeprecated; // cDepracateLoading::HandleAttributes marks this byte
    public:
        cLoadingInfo() : m_ExtraDisplayTime(0.0f), m_nGroup(0), m_bDeprecated(false)
        {
            m_NameHash[0] = 0;
            m_NameHash[1] = 0;
            m_NameHash[2] = 0;
            m_NameHash[3] = 0;
            m_word4C = 0;
        }
        virtual ~cLoadingInfo(); // CD2 calls this out of line at 0x828B0E00
        // CD2 registrar 0x83024828 registers factory 0x828B09A8 for a 0x54-byte class.
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        CD2_LAYOUT_CHECKS(cLoadingInfo,
            CD2_SIZE(cLoadingInfo, 0x54)
            CD2_OFFSET(cLoadingInfo, m_NameHash, 0x18)
            CD2_OFFSET(cLoadingInfo, m_ExtraDisplayTime, 0x28)
            CD2_OFFSET(cLoadingInfo, m_ImageFile, 0x2C)
            CD2_OFFSET(cLoadingInfo, m_nGroup, 0x48)
            CD2_OFFSET(cLoadingInfo, m_word4C, 0x4C)
            CD2_OFFSET(cLoadingInfo, m_bDeprecated, 0x50))
    };
}

#endif
