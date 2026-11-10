// GangManager::cAgressiveResponseConfigData: aggressive-response vehicle spawning limits, set from RWS attributes.
// Field names and order from RuffKing (CAttributeHandler + DynamicAllocationPolicy there). CD2's MakeNew (0x8266F888)
// allocates 0x60 bytes and inlines the constructor: CAttributeHandler, then the cScriptHost subobject at 0x18 (vtables
// 0x8212E7D0 at 0x18 and the shared registered-class table 0x820FC01C at 0x2C, as in cFactionConfigData), then
// 24 / 100 / 1000 at 0x34..0x3C, 20.0 / 3.0 / 10.0 / 50.0 at 0x40..0x4C and a cleared GUID at 0x50.
// The destructor (0x8266F9F8) restores the three vptrs and calls cScriptHost's (0x8276F0C0), then CAttributeHandler's.
// Primary slot 1 (HandleAttributes, 0x823B2298) lies in the order-list region; slot 12 is the shared Destruct body.
#ifndef GangManager_cAgressiveResponseConfigData_H
#define GangManager_cAgressiveResponseConfigData_H

#include "rws/attributes.h"
#include "fun_runtime/scripthost.h"
#include "cd2/layout.h"

namespace GangManager
{
    class cAgressiveResponseConfigData : public RWS::CAttributeHandler, public Fun_Runtime::cScriptHost
    {
    public:
        // __forceinline: CD2 inlines the constructor into MakeNew.
        __forceinline cAgressiveResponseConfigData(const RWS::CAttributePacket &)
            : m_nMaxNumVehicles(24), m_nMinTimeBetweenSpawnTicks(100), m_nMaxTimeBetweenSpawnTicks(1000),
              m_fMinSpawnPlayerSpeed(20.0f), m_fMaxSpawnPlayerSpeed(3.0f), m_fMinAVPadding(10.0f),
              m_fMaxAVPadding(50.0f)
        {
            m_nGlobalPKGangGUID.Clear();
        }
        virtual ~cAgressiveResponseConfigData();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        virtual void HandleAttributes(const RWS::CAttributePacket &);

        unsigned int m_nMaxNumVehicles;           // 0x34
        unsigned int m_nMinTimeBetweenSpawnTicks; // 0x38
        unsigned int m_nMaxTimeBetweenSpawnTicks; // 0x3C
        float m_fMinSpawnPlayerSpeed;             // 0x40
        float m_fMaxSpawnPlayerSpeed;             // 0x44
        float m_fMinAVPadding;                    // 0x48
        float m_fMaxAVPadding;                    // 0x4C
        RWS::RWSGUID m_nGlobalPKGangGUID;         // 0x50

        // CD2: cAgressiveResponseConfigData's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::cClass const & RetClass() const; // cRegisteredClass 0: 0x823E5800
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cRegisteredClass 1: 0x823E5810
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x823E5870
        virtual char const * RetName() const; // cSafeDeletable 4: 0x823E5880
    public:
        CD2_LAYOUT_CHECKS(cAgressiveResponseConfigData,
            CD2_SIZE(cAgressiveResponseConfigData, 0x60)
            CD2_OFFSET(cAgressiveResponseConfigData, m_nMaxNumVehicles, 0x34)
            CD2_OFFSET(cAgressiveResponseConfigData, m_fMinSpawnPlayerSpeed, 0x40)
            CD2_OFFSET(cAgressiveResponseConfigData, m_nGlobalPKGangGUID, 0x50))
    };
}

#endif
