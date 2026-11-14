// Vehicle::cHelicopter (Crackdown 2): base cVehicle (CD2 inheritance registrar 0x82FE84E8), size 0x2DB0 (registrar and
// StaticCreateClass). Only the fields a matched function uses are modelled.
#ifndef Vehicle_cHelicopter_H
#define Vehicle_cHelicopter_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "gom/object_prototype.h"
#include "Vehicle/cVehicle.h"
#include "Vehicle/cPintleMount.h"
#include "gom/cPointOfInterest.h"
#include "PHYSICS/cDynamicBodyInteractionData.h"

namespace Vehicle
{
    class cHelicopter : public cVehicle
    {
    public:
        // CD2 helicopter table overrides the vehicle engine-start slot with an empty body.
        virtual void StartEngine();

        // Name, base and size (0x4C0) from RuffKing; CD2's MakeNew (0x826B8A78) allocates 0x4C0 bytes and calls the
        // constructor at 0x826B8D10. m_fMaxThrustVelo (RuffKing 0x368) is what cHelicopterController::AssignVehicle
        // copies as the controller's default maximum speed.
        class cHeliPrototype : public cVehicle::cVehiclePrototype
        {
        public:
            cHeliPrototype(const RWS::CAttributePacket &);   // CD2 0x826B8D10

        private:
            unsigned char m_unmodelled350[0x368 - 0x350];

        public:
            float m_fMaxThrustVelo;                         // 0x368

        private:
            unsigned char m_unmodelled36C[0x4C0 - 0x36C];

            // CD2: cHeliPrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x826E1B70
        private:
            CD2_LAYOUT_CHECKS(cHeliPrototype,
                CD2_SIZE(cHeliPrototype, 0x4C0)
                CD2_OFFSET(cHeliPrototype, m_fMaxThrustVelo, 0x368))
        };

        // CD2 spawning initializer 0x82FE85A0 names placement factory 0x826b8ae0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcHelicopterClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x826B8A78, registered by the class-factory registrar (0x82FE8550).
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // Registered-class table 0x82134728: slot 0 (0x826B8A08) and slot 1 (0x826B8A18).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 placement factory 0x826B8AE0 forwards only this.
        cHelicopter();                                      // CD2 0x82231520
        virtual ~cHelicopter();                             // CD2 0x826B9DE0 (cWeaponisedHelicopter's destructor calls it)

        // cVehicle slot 360, CD2 0x826B8AF8 (RuffKing declares the override).
        virtual float RetTheoreticalMaxMPH();
        // Own virtuals, RuffKing's two in its order: CD2 slots 442 and 443 (0x826B8B10 indexes m_aTurrets).
        virtual cGameBase *RetCarrierObject();
        virtual cPintleMount *RetPintleMount(unsigned char nIdx);
        // CD2 table 0x820168E8 overrides these cVehicle entries; inherited by the weaponised helicopter. Slots 122 and
        // 123 are RuffKing's RetPointOfInterest and RetNumPointsOfInterest (its bodies are CD2's 0x826BDCC8/0x826BDCC0).
        virtual Fun_Runtime::RetVal Term(); // primary slot 6: 0x826BB898
        virtual bool EnterPhysicalState(); // primary slot 7: 0x821D9BF0
        virtual void Slot13(); // primary slot 13: 0x8220A460
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // primary slot 18: 0x826BA050
        virtual void Slot23(); // primary slot 23: 0x8236D6D8
        virtual void Slot24(); // primary slot 24: 0x8236FFA8
        virtual Fun_Runtime::RetVal Slot37(); // primary slot 37: 0x821FDD20
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // primary slot 38: 0x826BBCE0
        virtual Fun_Runtime::RetVal TermForReuse(); // primary slot 39: 0x826BBAB0
        virtual GOM::cPointOfInterest *RetPointOfInterest(int nPoint); // primary slot 122: 0x826BDCC8
        virtual unsigned char RetNumPointsOfInterest(); // primary slot 123: 0x826BDCC0
        virtual void vf127(); // primary slot 127: 0x823938C8
        virtual void vf140(); // primary slot 140: 0x826BB3A8
        virtual void vf143(); // primary slot 143: 0x826BE8F0
        virtual void vf322(); // primary slot 322: 0x8222D250
        virtual void vf323(); // primary slot 323: 0x826BD950
        virtual void vf340(); // primary slot 340: 0x82387798
        virtual void vf341(); // primary slot 341: 0x826F7B10
        virtual void vf365(); // primary slot 365: 0x826BE4C8
        virtual void vf391(); // primary slot 391: 0x826BE460
        virtual void vf414(); // primary slot 414: 0x8288FB78
        virtual void LeavePhysicalState(); // primary slot 27: 0x826BD9C0
        virtual void Slot57(); // primary slot 56: 0x826BDBF0
        virtual void Slot58(); // primary slot 57: 0x826BDC60
        virtual void Slot59(); // primary slot 58: 0x826BDC28
        virtual void vf105(); // primary slot 105: 0x826C0188
        virtual void vf139(); // primary slot 139: 0x826BDA08
        virtual void vf217(); // primary slot 217: 0x826BE560
        virtual void UpdateCollisionLayer(); // primary slot 315: 0x823A9F90
        virtual void vf325(); // primary slot 325: 0x8288FB78
        virtual bool IsOnGround(); // primary slot 372: 0x826BDC98
        virtual void vf374(); // primary slot 374: 0x826BD628
        virtual void vf376(); // primary slot 376: 0x826BDB58
        virtual bool CheckForReplicationActivation(unsigned int *nRetCode); // primary slot 377: 0x826BD668
        virtual void vf380(); // primary slot 380: 0x826BB158
        virtual void vf392(); // primary slot 392: 0x826BB0F8
        virtual void vf393(); // primary slot 393: 0x826BAFB8
        virtual void vf394(); // primary slot 394: 0x826BB0F8
        virtual void vf413(); // primary slot 413: 0x826BA5D0
        virtual void vf415(); // primary slot 415: 0x827E56A8
        virtual bool IsOkToInteract(); // primary slot 418: 0x826BDEB0
        virtual void HandleTryToSwapSeatsInteractionPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // primary slot 423: 0x826F7B50
        virtual void HanldTryToEjectInteractPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // primary slot 426: 0x826F7B68
        virtual void HandleTryToExitInteractPermisiionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // primary slot 427: 0x826BDDD8
        virtual void HandleTryToEnterInteractPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); // primary slot 428: 0x826BDDA0
        virtual void CalculateLOD(int); // replication slot 3: 0x826BD6C0


    private:
        unsigned char m_unmodelled1740[0x17EA - 0x1740];
        // RuffKing's names and count (7); CD2's RetPointOfInterest (0x826BDCC8) bounds the index by the count.
        unsigned char m_nPoiCount;                          // 0x17EA
        unsigned char m_unmodelled17EB[0x17F0 - 0x17EB];
        GOM::cPointOfInterest m_POI[7];                     // 0x17F0
        unsigned char m_unmodelled1940[0x1948 - 0x1940];

    public:
        cHeliPrototype *m_pHeliPrototype;                   // 0x1948 (RuffKing's name)

    private:
        unsigned char m_unmodelled194C[0x1AA0 - 0x194C];
        // RuffKing's names, 0xA0 above its offsets as the fields around them; CD2's HandleTryToEnterInteractPermission-
        // Query (0x826BDDA0) compares the arm rotations and tests the deploy flag.
        float m_fMinArmRot;                                 // 0x1AA0
        float m_fMaxArmRot;                                 // 0x1AA4
        bool m_bDeployArms;                                 // 0x1AA8
        bool m_bForceDeployArms;                            // 0x1AA9
        float m_fCurrentArmRot;                             // 0x1AAC
        unsigned char m_unmodelled1AB0[0x1AC0 - 0x1AB0];
        cPintleMount m_aTurrets[2];                         // 0x1AC0 (RuffKing's name and count)
        unsigned char m_unmodelled1D60[0x1DFC - 0x1D60];
        // RuffKing's name, 0x1A0 above its offset as m_pCarriedObj; CD2's CheckForReplicationActivation (0x826BD668).
        unsigned int m_nAttachedObjectIDField;              // 0x1DFC
        unsigned char m_unmodelled1E00[0x2C14 - 0x1E00];
        // RuffKing's name and type; CD2's IsOnGround (0x826BDC98) tests it.
        Fun_Runtime::cSafeDeletablePointer<PHYSICS::cDynamicBody> m_pCarriedObj;   // 0x2C14
        unsigned char m_unmodelled2C24[0x2DB0 - 0x2C24];

        CD2_LAYOUT_CHECKS(cHelicopter,
            CD2_SIZE(cHelicopter, 0x2DB0)
            CD2_OFFSET(cHelicopter, m_pHeliPrototype, 0x1948)
            CD2_OFFSET(cHelicopter, m_aTurrets, 0x1AC0)
            CD2_OFFSET(cHelicopter, m_nPoiCount, 0x17EA)
            CD2_OFFSET(cHelicopter, m_POI, 0x17F0)
            CD2_OFFSET(cHelicopter, m_fMinArmRot, 0x1AA0)
            CD2_OFFSET(cHelicopter, m_bDeployArms, 0x1AA8)
            CD2_OFFSET(cHelicopter, m_fCurrentArmRot, 0x1AAC)
            CD2_OFFSET(cHelicopter, m_nAttachedObjectIDField, 0x1DFC)
            CD2_OFFSET(cHelicopter, m_pCarriedObj, 0x2C14))
    };
}

#endif
