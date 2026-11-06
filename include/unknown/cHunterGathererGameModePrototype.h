// STAND-IN: CD2 constructor 0x8287E2B0 calls cPvPGameModePrototype (0x8283E2F8).
// Table 0x8215FA70 adds the getters at slots 44..51. Parameter names are ours:
// their meanings are not recovered, so names describe their types and CD2 offsets.
#ifndef unknown_cHunterGathererGameModePrototype_H
#define unknown_cHunterGathererGameModePrototype_H
#include "GameManagement/cPvPGameModePrototype.h"
namespace unknown
{
    class cHunterGathererGameModePrototype : public GameManagement::cPvPGameModePrototype
    {
    public:
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual int RetStringID() const;
        virtual void Destruct();
        virtual float RetFloat148() const;
        virtual float RetFloat14C() const;
        virtual float RetFloat150() const;
        virtual bool RetFlag154() const;
        virtual bool RetFlag155() const;
        virtual bool RetFlag174() const;
        virtual float RetFloat178() const;
        virtual float RetFloat17C() const;
        virtual int RetEffectID(unsigned int index) const;
        // CD2 slots 53..55 copy four-byte aggregates; their types remain unidentified.
        virtual void vf53();
        virtual void vf54();
        virtual void vf55();
        // Out of line: CD2 0x8287E2B0 (MakeNew calls it).
        cHunterGathererGameModePrototype();
    private:
        float m_fParameter148;
        float m_fParameter14C;
        float m_fParameter150;
        bool m_bParameter154;
        bool m_bParameter155;
        // Attribute cases 10..16 resolve effect names through cParticleEffectManager::RetEffectId.
        int m_aEffectIDs[7];
        bool m_bParameter174;
        float m_fParameter178;
        float m_fParameter17C;
        unsigned char m_unmodelled180[0x18C - 0x180];
        int m_nParameter18C;
        float m_fParameter190;
        unsigned char m_unmodelled194[4];
        CD2_LAYOUT_CHECKS(cHunterGathererGameModePrototype,
            CD2_SIZE(cHunterGathererGameModePrototype, 0x198)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_fParameter148, 0x148)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_fParameter14C, 0x14C)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_fParameter150, 0x150)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_bParameter154, 0x154)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_bParameter155, 0x155)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_bParameter174, 0x174)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_fParameter178, 0x178)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_fParameter17C, 0x17C)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_aEffectIDs, 0x158)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_nParameter18C, 0x18C)
            CD2_OFFSET(cHunterGathererGameModePrototype, m_fParameter190, 0x190))
    };
}
#endif
