#ifndef CHARACTER_cCharacterGlobalDlcProfile_H
#define CHARACTER_cCharacterGlobalDlcProfile_H

#include "rws/attributes.h"
#include "rws/dynamicallocationpolicy.h"
#include "cd2/layout.h"

namespace Equip { class cBulletData; }
namespace GOM { class cObjectPrototype; }

namespace CHARACTER
{
    class cCharacterGlobalDlcProfile;
    extern cCharacterGlobalDlcProfile *g_pCharGlobalDlcProfile;

    // RuffKing names and member order; CD2 factory 0x82552490 establishes the
    // initialized fields and singleton assignment. The own block ends at 0xA8.
    class cCharacterGlobalDlcProfile : public RWS::CAttributeHandler, public RWS::DynamicAllocationPolicy
    {
    public:
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        virtual void Destruct(); // CD2 table 0x82114058 slot 12
        virtual void HandleAttributes(const RWS::CAttributePacket &);
        virtual bool HandleDataInNewDesignBuild() { return true; }
        cCharacterGlobalDlcProfile();
        // CD2 0x82552590 clears the singleton before CAttributeHandler cleanup.
        virtual ~cCharacterGlobalDlcProfile();

    private:
        void SetDefaults(); // Reference helper; CD2 inlines its defaults into the factory.
        float m_fKickDistance;
        float m_fThrowDistance;
        float m_fSuperSwimTopSpeed;
        float m_fSuperSwimAccelPerSec;
        float m_fSuperSpeedTopSpeed;
        float m_fSuperSpeedAccelPerSec;
        float m_fSuperSpeedMaxFOVIncrease;
        float m_fSuperSpeedMaxFovIncresePerSecond;
        float m_fSuperSpeedMaxFovDecreasePerSecond;
        float m_fSuperSpeedTimeToDefaultFOV;
        float m_fSuperSpeedTimeToDefaultFOVStopped;
        float m_fJumpLargeHeight;
        float m_fJumpFallDistanceToDeath;
        float m_fChopperCamSpeed;
        float m_fMachineGunCarCamSpeed;
        float m_fRocketGunCarCamSpeed;
        float m_fPassengerCarCamSpeed;
        float m_fMachineGunCarAccuracy;
        float m_fRocketGunCarAccuracy;
        int m_nRocketGunCarExplosivelevel;
        float m_fGunCarLookSpringTimeout;
        float m_fRocketGunCarRocketSpeed;
        int m_fRocketGunCarMuzzleEffectID;
        int m_fMachineGunCarMuzzleEffectID;
        int m_fMachineGunShellEffectID;
        Equip::cBulletData *m_pBulletData;
        float m_fMachineGunCarCrosshairHeight;
        float m_fRocketGunCarCrosshairHeight;
        float m_fMachineGunCarLookSpringSpeed;
        float m_fRocketGunCarLookSpringSpeed;
        float m_fRocketGunCarSelfDamageTweak;
        float m_fRocketGunCarMinCameraAng;
        float m_fMachineGunCarMinCameraAng;
        float m_fRocketGunCarTurretModelLag;
        float m_fMachineGunCarTurretModelLag;
        GOM::cObjectPrototype *m_pRocketProto;

        CD2_LAYOUT_CHECKS(cCharacterGlobalDlcProfile,
            CD2_SIZE(cCharacterGlobalDlcProfile, 0xA8)
            CD2_OFFSET(cCharacterGlobalDlcProfile, m_fKickDistance, 0x18)
            CD2_OFFSET(cCharacterGlobalDlcProfile, m_fSuperSwimTopSpeed, 0x20)
            CD2_OFFSET(cCharacterGlobalDlcProfile, m_fSuperSpeedTopSpeed, 0x28)
            CD2_OFFSET(cCharacterGlobalDlcProfile, m_fJumpFallDistanceToDeath, 0x48)
            CD2_OFFSET(cCharacterGlobalDlcProfile, m_pBulletData, 0x7C)
            CD2_OFFSET(cCharacterGlobalDlcProfile, m_pRocketProto, 0xA4))
    };
}

#endif
