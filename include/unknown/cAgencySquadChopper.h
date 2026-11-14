#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cAgencySquadChopper (Crackdown 2): STAND-IN. Base Vehicle::cVehicle: CD2's inheritance registrar (0x82FEBD00)
// names it and the constructor (0x826EEEF8) calls cVehicle's (0x826CCD70) first. StaticCreateClass (0x826EDBC8) builds
// cClass(0x12066, "cAgencySquadChopper", 0x2360); 0x2360 is the size its registrar gives. Own fields not modelled.
#ifndef UNKNOWN_CAGENCYSQUADCHOPPER_H
#define UNKNOWN_CAGENCYSQUADCHOPPER_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cVehicle.h"
#include "Vehicle/cPintleMount.h"

namespace unknown
{
    class cAgencySquadChopper : public Vehicle::cVehicle
    {
    public:
        // CD2 0x826EEEF8; the placement factory (0x826EDB60) forwards only this.
        cAgencySquadChopper();
        // CD2 0x826EDB50: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEBDB8 names placement factory 0x826edb60.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySquadChopperClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2's deleting destructor (0x826EF500) is slot 0 of the primary table (0x821378E8).
        virtual ~cAgencySquadChopper();

        // The other slots where CD2's table differs from cVehicle's; names and signatures are the bases'. Slot 360 holds
        // cHelicopter's RetTheoreticalMaxMPH body (0x826B8AF8), 423 and 426 the bodies cHelicopter's table also has.
        virtual Fun_Runtime::RetVal Term(); // 6: 0x826F2870
        virtual void Slot13(); // 13: 0x826F2C30
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x826EFDF8
        virtual void Slot23(); // 23: 0x826F33D8
        virtual void Slot24(); // 24: 0x826F5E98
        virtual void LeaveRenderableState(); // 32: 0x826F5A98
        virtual Fun_Runtime::RetVal Slot37(); // 37: 0x826F2B48
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // 38: 0x826F2988
        virtual Fun_Runtime::RetVal TermForReuse(); // 39: 0x826F28F0
        virtual void vf76(); // 76: 0x826F2EB8
        virtual GOM::cPointOfInterest *RetPointOfInterest(int nPoint); // 122: 0x826F7B20
        virtual unsigned char RetNumPointsOfInterest(); // 123: 0x826F7B18
        virtual void vf127(); // 127: 0x826F77E8
        virtual void vf217(); // 217: 0x826F8FA0
        virtual void ProcessDynamicObjectTerm(unsigned char nNodeID, bool bForceDelete); // 305: 0x826F5E68
        virtual void UpdateCollisionLayer(); // 315: 0x826F35B0
        virtual void vf319(); // 319: 0x8288FB78
        virtual void vf322(); // 322: 0x826EDB78
        virtual void vf325(); // 325: 0x8288FB78
        virtual void vf340(); // 340: 0x826F7A70
        virtual void vf341(); // 341: 0x826F7B10
        virtual void StartEngine(); // 345: 0x82580578
        virtual float RetTheoreticalMaxMPH(); // 360: 0x826B8AF8
        virtual void vf365(); // 365: 0x826F8340
        virtual bool IsOnGround(); // 372: 0x826F7A68
        virtual bool CheckForReplicationActivation(unsigned int *nRetCode); // 377: 0x826F5C50
        virtual void vf380(); // 380: 0x826F0910
        virtual void vf391(); // 391: 0x826F8060
        virtual void vf395(); // 395: 0x827E56A8
        virtual void vf413(); // 413: 0x826F0288
        virtual void vf414(); // 414: 0x8288FB78
        virtual void vf415(); // 415: 0x827E56A8
        virtual bool IsOkToInteract(); // 418: 0x826F7B88
        virtual void HandleTryToSwapSeatsInteractionPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // 423: 0x826F7B50
        virtual void HanldTryToEjectInteractPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // 426: 0x826F7B68
        virtual void HandleTryToExitInteractPermisiionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // 427: 0x826F7B80
        virtual void vf436(); // 436: 0x827E56A8
        virtual void vf437(); // 437: 0x826EF708
        virtual void vf438(); // 438: 0x826EF680
        virtual void vf439(); // 439: 0x826EF550
        // Own virtuals 442..444, in cHelicopter's order and with its names: 443 (0x826EDBB0) indexes m_aTurrets as
        // cHelicopter's RetPintleMount does, 442 holds the shared false stub.
        virtual cGameBase *RetCarrierObject();
        virtual Vehicle::cPintleMount *RetPintleMount(unsigned char nIdx);
        virtual void vf444();                                                   // 444: 0x826EF750

    private:
        unsigned char m_unmodelled1740[0x1DD0 - 0x1740];
        // Name and count as cHelicopter's (RuffKing); RetPintleMount (0x826EDBB0) steps 0x150 bytes.
        Vehicle::cPintleMount m_aTurrets[2];                                    // 0x1DD0
        unsigned char m_unmodelled2070[0x2360 - 0x2070];

        CD2_LAYOUT_CHECKS(cAgencySquadChopper,
            CD2_SIZE(cAgencySquadChopper, 0x2360)
            CD2_OFFSET(cAgencySquadChopper, m_aTurrets, 0x1DD0))
    };
}

#endif // UNKNOWN_CAGENCYSQUADCHOPPER_H
