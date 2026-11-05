// ZoneManager::cVOAZone: STAND-IN. Base and m_strName from RuffKing; CD2's destructor (0x8280EA70) frees a narrow string at
// 0xE0 and restores cPlayerTriggerZone's tables before calling cPlayerTriggerBase's destructor. Size 0x100 (registrar).
#ifndef ZoneManager_cVOAZone_H
#define ZoneManager_cVOAZone_H

#include "ZoneManager/cPlayerTriggerZone.h"
#include "fun_runtime/stringc.h"
#include "cd2/layout.h"

namespace ZoneManager
{
    class cVOAZone : public cPlayerTriggerZone
    {
    public:
        // __forceinline: CD2 inlines it into MakeNew (0x8280E980).
        __forceinline cVOAZone(const RWS::CAttributePacket &) : cPlayerTriggerZone(false) {}
        virtual ~cVOAZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        Fun_Runtime::cStringc m_strName;            // 0xE0

        CD2_LAYOUT_CHECKS(cVOAZone,
            CD2_SIZE(cVOAZone, 0x100)
            CD2_OFFSET(cVOAZone, m_strName, 0xE0))
    };
}

#endif
