#include "cd2/layout.h"
#include "rws/attributes.h"
#ifndef GameManagement_cNetGameSpawnPoint_H
#define GameManagement_cNetGameSpawnPoint_H

#include "GameManagement/cGameModeSpawnPoint.h"
#include "fun_runtime/stringc.h"

namespace GameManagement
{
    // Base relationship from RuffKing's PDB; this stand-in models no additional fields yet.
    class cNetGameSpawnPoint : public cGameModeSpawnPoint
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual ~cNetGameSpawnPoint();
        virtual int RetArenaIndex() const { return m_nArenaIndex; }
    public:
        // Out of line: CD2 0x8284D908 (MakeNew calls it).
        cNetGameSpawnPoint();

    private:
        // RuffKing names; CD2 constructor/destructor use the same offsets.
        Fun_Runtime::cStringc m_sArenaName;
        int m_nArenaIndex;

        CD2_LAYOUT_CHECKS(cNetGameSpawnPoint,
            CD2_SIZE(cNetGameSpawnPoint, 0x80)
            CD2_OFFSET(cNetGameSpawnPoint, m_sArenaName, 0x60)
            CD2_OFFSET(cNetGameSpawnPoint, m_nArenaIndex, 0x7C))

    };
}

#endif
