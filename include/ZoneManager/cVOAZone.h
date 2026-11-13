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
        // The reference declares both callbacks; CD2 installs concrete entries at primary slots 16 and 17.
        virtual void OnPlayerEnter(CHARACTER::cCharacter *);
        virtual void OnPlayerLeave(CHARACTER::cCharacter *);
        // __forceinline: CD2 inlines it into MakeNew (0x8280E980).
        __forceinline cVOAZone(const RWS::CAttributePacket &) : cPlayerTriggerZone(false) {}
        virtual ~cVOAZone();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // RuffKing declares these overrides; CD2's load/save table points to
        // 0x8280EDB0 and 0x8280EE30 instead of the inherited empty bodies.
        virtual void Load(SaveGame::cLoadStream *);
        virtual void Save(SaveGame::cSaveStream *);

    private:
        Fun_Runtime::cStringc m_strName;            // 0xE0

        // CD2: cVOAZone's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8280EB08
    private:
        CD2_LAYOUT_CHECKS(cVOAZone,
            CD2_SIZE(cVOAZone, 0x100)
            CD2_OFFSET(cVOAZone, m_strName, 0xE0))
    };
}

#endif
