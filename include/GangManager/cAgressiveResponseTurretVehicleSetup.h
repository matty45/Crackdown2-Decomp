#include "rws/attributes.h"
// GangManager::cAgressiveResponseTurretVehicleSetup (Crackdown 2): STAND-IN with only what its matched functions need; its bases are not modelled yet.
// Its class-factory registrar (0x82FDBE70) registers "cAgressiveResponseTurretVehicleSetup" with MakeNew (0x82672A40) and size 0x68.
// Reconstruction update: the reference base and complete CD2 layout are modelled below.
#ifndef GANGMANAGER_CAGRESSIVERESPONSETURRETVEHICLESETUP_H
#define GANGMANAGER_CAGRESSIVERESPONSETURRETVEHICLESETUP_H
#include "editor/guid_event_handler.h"
#include "GangManager/tAgressiveResponseTurretTeamTemplate.h"

namespace GangManager
{
    // Burn's base; CD2 table 0x8212E860 appends RetClassName at slot 11.
    class cAgressiveResponseTurretVehicleSetup : public RWS::CAttributeHandler
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // CD2 inlines construction into MakeNew, resetting the arrays before
        // storing the probability and valid-level bounds.
        // Without __forceinline, XDK leaves the constructor out of line (6/62 LTCG words).
        __forceinline cAgressiveResponseTurretVehicleSetup(const RWS::CAttributePacket &)
        {
            ResetTemplateData();
            m_nValidFromLevel = 1;
            m_nValidToLevel = 5;
            m_fProbability = 0.1f;
        }
        virtual ~cAgressiveResponseTurretVehicleSetup() {}
        virtual void HandleAttributes(const RWS::CAttributePacket &);
    protected:
        void ResetTemplateData()
        {
            for (int i = 0; i < tAgressiveResponseTurretTeamTemplate::nMAX_TURRET_PROTOTYPES; ++i)
            {
                // CD2 clears the gunner, turret, then weapon entries in this loop.
                m_TurretTeamTemplate.apGunnerPrototypes[i] = 0;
                m_TurretTeamTemplate.apTurretPrototypes[i] = 0;
                m_TurretTeamTemplate.apWeaponPrototypes[i] = 0;
            }
            m_TurretTeamTemplate.pVehiclePrototype = 0;
            m_TurretTeamTemplate.pDriverPrototype = 0;
            m_TurretTeamTemplate.nNumTurrets = 0;
            m_TurretTeamTemplate.nARTurretIndex = tAgressiveResponseTurretTeamTemplate::nINVALID_AR_INDEX;
        }
        Editor::cGUIDEventHandler<cAgressiveResponseTurretVehicleSetup> m_EventHandler;
        tAgressiveResponseTurretTeamTemplate m_TurretTeamTemplate;
        float m_fProbability;
        unsigned char m_nValidFromLevel;
        unsigned char m_nValidToLevel;

        CD2_LAYOUT_CHECKS(cAgressiveResponseTurretVehicleSetup,
            CD2_SIZE(cAgressiveResponseTurretVehicleSetup, 0x68)
            CD2_OFFSET(cAgressiveResponseTurretVehicleSetup, m_EventHandler, 0x18)
            CD2_OFFSET(cAgressiveResponseTurretVehicleSetup, m_TurretTeamTemplate, 0x2C)
            CD2_OFFSET(cAgressiveResponseTurretVehicleSetup, m_fProbability, 0x60)
            CD2_OFFSET(cAgressiveResponseTurretVehicleSetup, m_nValidFromLevel, 0x64)
            CD2_OFFSET(cAgressiveResponseTurretVehicleSetup, m_nValidToLevel, 0x65))
    };
}

#endif // GANGMANAGER_CAGRESSIVERESPONSETURRETVEHICLESETUP_H
