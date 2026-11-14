#ifndef Billboard_BillboardProfile_H
#define Billboard_BillboardProfile_H

#include "rws/attributes.h"
#include "fun_runtime/vector.h"

namespace Billboard
{
    class BillboardData;
    // STAND-IN: member names/order from RuffKing; CD2 factory 0x829128E0
    // and destructor 0x82912A10 confirm the three vectors and complete size.
    class BillboardProfile : public RWS::CAttributeHandler
    {
    public:
        BillboardProfile();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct(); // CD2 primary slot 12, shared empty body.
        virtual ~BillboardProfile();
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    protected:
        Fun_Runtime::cVector<BillboardData *> m_vBeaconNumberVideos;
        Fun_Runtime::cVector<BillboardData *> m_vAgentAppreciationVideos;
        Fun_Runtime::cVector<BillboardData *> m_vPSAVideos;
        BillboardData *m_pAgentAppreciationStrengthLevel[5];
        unsigned int m_nNumBulletinPlays;
        unsigned int m_nNumPSAPlays;

        CD2_LAYOUT_CHECKS(BillboardProfile,
            CD2_SIZE(BillboardProfile, 0x64)
            CD2_OFFSET(BillboardProfile, m_vBeaconNumberVideos, 0x18)
            CD2_OFFSET(BillboardProfile, m_vAgentAppreciationVideos, 0x28)
            CD2_OFFSET(BillboardProfile, m_vPSAVideos, 0x38)
            CD2_OFFSET(BillboardProfile, m_pAgentAppreciationStrengthLevel, 0x48)
            CD2_OFFSET(BillboardProfile, m_nNumBulletinPlays, 0x5C))
    };
    extern BillboardProfile *g_pBillboardProfile;
}

#endif
