#include "rws/attributes.h"
#ifndef GameManagement_cNetGamePlayerSpawnPoint_H
#define GameManagement_cNetGamePlayerSpawnPoint_H

#include "GameManagement/cNetGameSpawnPoint.h"

namespace GameManagement
{
    enum etPlayerSpawnPointType
    {
        ePSPT_None = 0,
        ePSPT_Solo,
        ePSPT_Team
    };

    // Reference names/layout checked against CD2's factory and timing methods.
    class cNetGamePlayerSpawnPoint : public cNetGameSpawnPoint
    {
    public:
        cNetGamePlayerSpawnPoint()
            : m_nTeamID(0), m_ePlayerSpawnPointType(ePSPT_None), m_nReactivateTime(0) {}
        // CD2 0x8284C318 restores the derived primary vptr before base cleanup.
        virtual ~cNetGamePlayerSpawnPoint() {}
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        void SetInactive(unsigned int nDuration);
        virtual bool IsActive() const;
    protected:
        unsigned char m_nTeamID;
        etPlayerSpawnPointType m_ePlayerSpawnPointType;
        unsigned int m_nReactivateTime;
        CD2_LAYOUT_CHECKS(cNetGamePlayerSpawnPoint,
            CD2_SIZE(cNetGamePlayerSpawnPoint, 0x90)
            CD2_OFFSET(cNetGamePlayerSpawnPoint, m_nTeamID, 0x80)
            CD2_OFFSET(cNetGamePlayerSpawnPoint, m_ePlayerSpawnPointType, 0x84)
            CD2_OFFSET(cNetGamePlayerSpawnPoint, m_nReactivateTime, 0x88))
    };
}

#endif
