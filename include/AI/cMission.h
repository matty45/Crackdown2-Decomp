// STAND-IN: RuffKing cMission derives from cMissionBase. CD2 constructor 0x824592E8
// calls 0x8245A748 first; descriptor 0x82459250 names cMission (complete size 0x3C0).
// Fields beyond the known interfaces are not modelled; this is not an allocation layout.
#ifndef AI_CMISSION_H
#define AI_CMISSION_H
#include "AI/cMissionBase.h"
namespace AI
{
    class cMission : public cMissionBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        cMission();
        virtual ~cMission();
        // Overrides named by the reference mission interface.
        virtual bool IsOwnedLocally();
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const;
        virtual unsigned int GetMaxReplicatedFields() const;
    };
}
#endif
