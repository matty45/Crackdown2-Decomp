// ZoneManager::cAmbienceZone: STAND-IN. Base and m_strName from RuffKing; CD2's destructor (0x8280F9B8) frees a wide string at
// 0xE0 before cPlayerTriggerBase's destructor. Size 0x100 (registrar); RuffKing's debug colour is absent.
#ifndef ZoneManager_cAmbienceZone_H
#define ZoneManager_cAmbienceZone_H

#include "ZoneManager/cPlayerTriggerZone.h"
#include "fun_runtime/string.h"
#include "cd2/layout.h"

namespace ZoneManager
{
    class cAmbienceZone : public cPlayerTriggerZone
    {
    public:
        // The reference declares both callbacks; CD2 installs concrete entries at primary slots 16 and 17.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // __forceinline: CD2 inlines it into MakeNew (0x8280F8C0).
        __forceinline cAmbienceZone(const RWS::CAttributePacket &)
            : cPlayerTriggerZone(true), m_bPreviouslyEntered(false), m_bPreviouslyLeft(false), m_bIndoor(false) {}
        virtual ~cAmbienceZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;

    private:
        Fun_Runtime::cString m_strName;             // 0xE0
        // RuffKing's flags, without the debug colour before them (MakeNew clears 0xFC..0xFE).
        bool m_bPreviouslyEntered;                  // 0xFC
        bool m_bPreviouslyLeft;                     // 0xFD
        bool m_bIndoor;                             // 0xFE

        CD2_LAYOUT_CHECKS(cAmbienceZone,
            CD2_SIZE(cAmbienceZone, 0x100)
            CD2_OFFSET(cAmbienceZone, m_strName, 0xE0)
            CD2_OFFSET(cAmbienceZone, m_bPreviouslyEntered, 0xFC))
    };
}

#endif
