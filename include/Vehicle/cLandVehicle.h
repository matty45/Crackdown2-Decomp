// Vehicle::cLandVehicle (Crackdown 2): base cVehicle (CD2 inheritance registrar 0x82FE89B8), size 0x28C0 (registrar and
// StaticCreateClass; RuffKing's is the same). Only the members a matched function uses are modelled. RuffKing's
// m_pVehicleInstance (PHYSICS::cCustomVehicleInstance *, the Havok vehicle) is at 0x1DA4 in CD2; the small virtuals
// that read it wait for that Havok type.
#ifndef Vehicle_cLandVehicle_H
#define Vehicle_cLandVehicle_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "fun_runtime/retval.h"
#include "gom/object_prototype.h"
#include "Vehicle/cVehicle.h"
#include "Vehicle/cLVDamageEffect.h"

namespace PHYSICS { class cCustomVehicleInstance; }
class hkShape;
namespace VFX { class cAfterlightRounded; }
class hkTransform;

namespace Vehicle
{
    class cLandVehicleData;

    class cLandVehicle : public cVehicle
    {
    public:
        // Name, base and size (0x440) from RuffKing; CD2's MakeNew (0x826C0DB8) allocates 0x440 bytes and calls the
        // constructor at 0x826C6B90. The police-light settings below are named by RuffKing.
        class cLandVehiclePrototype : public cVehicle::cVehiclePrototype
        {
        public:
            // CD2's folded deleting wrapper 0x826EC1A0 restores this class's
            // table 0x8200352C, then calls cVehiclePrototype's destructor.
            virtual ~cLandVehiclePrototype() {}
            cLandVehiclePrototype(const RWS::CAttributePacket &);   // CD2 0x826C6B90
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);   // CD2 0x826C79B8

            // RuffKing names; CD2's IsAPoliceVehicle reads the flag at 0x368.
            char m_nLightType[10];
            float m_fPoliceLightSpeedModifier;
            float m_fShiftSpringK;
            float m_fShiftSpringD;
            // CD2 normalizes this byte on read (rather than returning a stored C++ bool directly).
            unsigned char m_bIsPoliceVehicle;

        private:
            unsigned char m_unmodelled369[0x440 - 0x369];

            // CD2: cLandVehiclePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x826C6D50
        private:
            CD2_LAYOUT_CHECKS(cLandVehiclePrototype,
                CD2_SIZE(cLandVehiclePrototype, 0x440)
                CD2_OFFSET(cLandVehiclePrototype, m_nLightType, 0x350)
                CD2_OFFSET(cLandVehiclePrototype, m_fPoliceLightSpeedModifier, 0x35C)
                CD2_OFFSET(cLandVehiclePrototype, m_fShiftSpringK, 0x360)
                CD2_OFFSET(cLandVehiclePrototype, m_fShiftSpringD, 0x364)
                CD2_OFFSET(cLandVehiclePrototype, m_bIsPoliceVehicle, 0x368))
        };

        // CD2 placement factory 0x826C0E20 forwards only this.
        cLandVehicle();                                     // CD2 0x826C1350
        // CD2 spawning initializer 0x82FE8A70 names placement factory 0x826c0e20.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static const Fun_Runtime::cClass *ms_pcLandVehicleClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2 0x826C0DB8, registered by the class-factory registrar (0x82FE8A20).
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        virtual const char *RetClassName() const;
        // Registered-class table 0x8213477C: slot 0 (0x826C0D48) and slot 1 (0x826C0D58).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        // CD2 virtual slots 326, 327, 353 and 363; names agree with the reference interfaces.
        virtual bool IsReversing();
        bool IsBraking();
        virtual bool IsHandbrakeOn();
        virtual void SetEngineDamage(float);
        virtual void SetSteeringAngle(float);
        // CD2 slot 417, 0x826C6B88; reference member name and offset agree.
        virtual void SetMustStop(bool);
        // CD2 primary slot 410 (0x826C4980), matching the reference police-light virtual order.
        virtual bool IsAPoliceVehicle();
        // CD2 0x826C2458; the deleting destructor 0x826C1878 calls it.
        virtual ~cLandVehicle();

        // CD2: cLandVehicle's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'),
        // an address its base's table does not hold there, so the class overrides it; names and signatures are the
        // bases'. Primary table 0x82019A18 (484 slots; the constructor 0x826C1350 installs it).
        virtual Fun_Runtime::RetVal Term();                     // 6: 0x826C1DC0
        virtual bool EnterPhysicalState();                      // 7: 0x822EAC18
        virtual void Slot13();                                  // 13: 0x826C2970
        virtual void Slot14();                                  // 14: 0x8221AE60
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);    // 18: 0x826C1980
        virtual void Slot23();                                  // 23: 0x822CB330
        virtual void Slot24();                                  // 24: 0x822ECE28
        virtual Fun_Runtime::RetVal Slot37();                                  // 37: 0x826C1CF8
        virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);    // 38: 0x826C1B58
        virtual Fun_Runtime::RetVal TermForReuse();             // 39: 0x826C1F88
        virtual void vf76();                                    // 76: 0x823568D0
        virtual void vf140();                                   // 140: 0x826C5B58
        virtual void vf143();                                   // 143: 0x82363D58
        virtual void vf144();                                   // 144: 0x826AB238
        virtual void vf152();                                   // 152: 0x826C79E0
        virtual void vf199();                                   // 199: 0x826C7A20
        virtual void vf200();                                   // 200: 0x826AB1C0
        virtual void vf202();                                   // 202: 0x826AB1B0
        virtual void vf203();                                   // 203: 0x826AB1B8
        virtual void FullySubmergedEvent();                                   // 224: 0x826C30B0
        virtual void vf238();                                   // 238: 0x826AB1E8
        virtual float RetFwdMPH();                                   // 240: 0x8236E908
        virtual void vf295();                                   // 295: 0x8229D758
        virtual void vf296();                                   // 296: 0x826C59E0
        virtual void vf319();                                   // 319: 0x826AB280
        virtual void vf321();                                   // 321: 0x826AB2A8
        virtual void vf340();                                   // 340: 0x826C2E48
        virtual void vf341();                                   // 341: 0x826C2FB0
        virtual void StartEngine();                             // 345: 0x82268F60
        virtual void StopEngine();                              // 346: 0x826C5CF0
        virtual bool IsFunctionallyDamaged();                                   // 347: 0x826C25D8
        virtual void vf351();                                   // 351: 0x8288FB78
        virtual void vf352();                                   // 352: 0x826C6020
        virtual float RetRoofCover();                                   // 354: 0x826C30D8
        virtual void vf355();                                   // 355: 0x826C67F8
        virtual float RetSteeringAngle();                                   // 358: 0x82269568
        virtual float RetSteeringMaxAngle();                                   // 359: 0x826C4900
        virtual float RetTheoreticalMaxMPH();                   // 360: 0x826AB190
        // 364: 0x826C4940. Name ours: CD2's slot after SetEngineDamage (not in RuffKing's table) returns the
        // multiplier SetEngineDamage stores, and cVehicle's copy (0x826B8928) returns 1.0.
        virtual float RetEngineDamage();
        virtual void vf365();                                   // 365: 0x826C60F8
        virtual void vf366();                                   // 366: 0x826C53C8
        virtual void vf367();                                   // 367: 0x826C64A0
        virtual void vf368();                                   // 368: 0x826C6578
        virtual void vf369();                                   // 369: 0x826C66B8
        virtual void EventPhysicsLODChange(unsigned char, unsigned char);   // 371: 0x8227D718
        virtual void vf396();                                   // 396: 0x8231FC80
        virtual bool IsTyreInflated(unsigned char nWheel);                                   // 406: 0x826AB218
        virtual bool AllTyresInflated();                                   // 407: 0x822E1A20
        virtual void ActivatePoliceLights(bool bActivate);                                   // 408: 0x82337B98
        virtual bool CanActivatePoliceLights();                                   // 409: 0x82291F80
        virtual bool RetPoliceLightsActivated();                                   // 411: 0x826AB270
        virtual void vf414();                                   // 414: 0x826AB248
        virtual bool MustStop();                                // 416: 0x826AB278
        // Slots 442..483 are cLandVehicle's own virtuals, in RuffKing's declaration order (RuffKing slots 400..442;
        // RuffKing's GetSuspensionLengthModifier, its slot 419, is not in CD2's table). CD2's bodies confirm the order:
        // the ramp getters return 0.0 and 300.0, RetDeliveryObject returns this, 449..451 read the light flags at
        // 0x2865..0x2867, 452/453 and 481/482 turn lights on and off, 461..464 are empty here and overridden by
        // cWheelGroup, and the exhaust queries 468/470 return true. Names RuffKing gives types not modelled here
        // (cFrame, hkShape, cLandVehicleData) keep their slot names.
        virtual float RetRampForceMagnitude();                                  // 442: 0x82457958
        virtual float RetRampForceSpeedThreshold();                             // 443: 0x828D83F8
        virtual float RetRamExplosionSpeedThreshold();                          // 444: 0x828D83F8
        virtual cGameBase *RetDeliveryObject();                                 // 445: 0x82580578
        virtual void vf446();                                                   // 446: 0x826C84D0 (RetEquipAttachFrame)
        virtual void OverrideProfileParams();                                   // 447: 0x82580578
        virtual void ActionUpdate(float);                                       // 448: 0x82580578
        virtual bool RetLightsOn();                                             // 449: 0x826AB258
        virtual bool RetPoliceLightsOn();                                       // 450: 0x826AB260
        virtual bool RetVehicleLightsActivated();                               // 451: 0x826AB268
        virtual void TurnOnVehicleLights();                                     // 452: 0x826C5268
        virtual void TurnOffVehicleLights(bool bForce);                         // 453: 0x826C5308
        virtual unsigned char RetNumMeleeAttackPositions() const;               // 454: 0x82889A60
        virtual const Fun_Runtime::Vec3 &RetMeleeAttackPosition(unsigned char); // 455: 0x826C6860
        virtual void UpdateAerial(float);                                       // 456: 0x82300AC8
        virtual void UpdateSimpleAerial(float);                                 // 457: 0x826C36D0
        virtual void SpawnMuzzleEffect(int, Fun_Runtime::Mtx *);                // 458: 0x826C3108
        virtual void UpdateAttachedMuzzleEffect(Fun_Runtime::Mtx *);            // 459: 0x826C3570
        virtual void CustomiseShape(hkShape **ppCollisionShape, cLandVehicleData *pVehicleData);                                                   // 460: 0x826C7B00 (CustomiseShape)
        // Slot 151 override, declared after its slot-460 overload: declared first, it pulls the new overload to 442.
        virtual void CustomiseShape(hkShape **ppCollisionShape);                                   // 151: 0x826C79C8
        virtual void ProcessControls(float);                                    // 461: 0x82580578
        virtual void UpdateWheelModels(const hkTransform &, float);             // 462: 0x82580578
        virtual void UpdateWheelInfo();                                         // 463: 0x82580578
        virtual void UpdateSkids(float);                                        // 464: 0x82580578
        virtual void DetectWheelSpinMode();                                     // 465: 0x826C5F28
        virtual void CalcIsSleeping(float);                                     // 466: 0x82307238
        virtual void UpdateAudioDetails(float);                                 // 467: 0x822C6400
        virtual bool SpawnExhaustVFX();                                         // 468: 0x8288FB78
        virtual void UpdateExhaustVFX(float);                                   // 469: 0x82345420
        virtual bool IsExhaustActive(unsigned char);                            // 470: 0x8288FB78
        virtual bool CanTurnOnExhaustFumes();                                   // 471: 0x826C2BB0
        virtual void AddVehicleLights();                                        // 472: 0x826C2170
        virtual void RemoveVehicleLights();                                     // 473: 0x826C2288
        virtual void ResetDamagedLights();                                      // 474: 0x826C5770
        virtual void ActivateVehicleLights(bool bActivate);                     // 475: 0x826C51E8
        virtual void UpdateLightVFX();                                          // 476: 0x82269020
        virtual bool CanActivateVehicleLights();                                // 477: 0x826C2A90
        virtual bool CanTurnOnVehicleLights();                                  // 478: 0x82336770
        virtual void TurnOnAfterlights();                                       // 479: 0x823575B8
        virtual void DamageAfterlights();                                       // 480: 0x82378B78
        virtual void TurnOnPoliceLights();                                      // 481: 0x826C4998
        virtual void TurnOffPoliceLights(bool bForce);                          // 482: 0x826C5128
        virtual bool CanTurnOnPoliceLights();                                   // 483: 0x826C2B30
        // Secondary tables: CEventHandler 0x82001B30, cReplicatedClass 0x820053A0, cSatchelChargeTarget 0x82001D98.
        virtual void HandleEvents(RWS::CMsg &);                 // CEventHandler 5: 0x826C2C48
        virtual void ReplicateInitialFields();                  // cReplicatedClass 8: 0x826C83A0
        virtual void ReplicateFields();                         // cReplicatedClass 9: 0x826C83E8
        virtual unsigned int GetMaxReplicatedFields() const;    // cReplicatedClass 23: 0x8288E110
        virtual bool CanHaveAttachedSatchelCharge(const Fun_Runtime::Vec3 &) const;    // cSatchelChargeTarget 1: 0x82387DA0

    private:
        // RuffKing's name and type, its first member as here; CD2's CustomiseShape (0x826C79C8) passes it on.
        cLandVehicleData *m_pVehicleData;                               // 0x1740
        unsigned char m_unmodelled1744[0x1B58 - 0x1744];
        cLVDamageEffect m_DamageEffect;                                 // 0x1B58 (RuffKing's name)
        unsigned char m_unmodelled1CF8[0x1DA4 - 0x1CF8];
        PHYSICS::cCustomVehicleInstance *m_pVehicleInstance;
        unsigned char m_unmodelled1DA8[0x26E0 - 0x1DA8];
        // RuffKing's names and offsets from here to m_bMustStop; CD2's light virtuals (0x826C51E8..0x826C5308) use
        // them at the same offsets.
        int m_LastUpdateTimestamp;                                      // 0x26E0
        unsigned char m_unmodelled26E4[0x2730 - 0x26E4];
        VFX::cGlobalLight *m_apHeadLightLargeVFX[6];                    // 0x2730
        VFX::cGlobalLight *m_apHeadLightSmallVFX[4];                    // 0x2748
        VFX::cGlobalLight *m_apBreakLightVFX[4];                        // 0x2758
        VFX::cGlobalLight *m_apTailLightVFX[4];                         // 0x2768
        VFX::cGlobalLight *m_apReverseLightVFX[4];                      // 0x2778
        VFX::cGlobalLight *m_apPoliceLightFrontVFX[3];                  // 0x2788
        VFX::cGlobalLight *m_apPoliceLightBackVFX[3];                   // 0x2794
        VFX::cGlobalLight *m_apPoliceLightRedVFX[4];                    // 0x27A0
        VFX::cGlobalLight *m_apPoliceLightBlueVFX[4];                   // 0x27B0
        VFX::cGlobalLight *m_apConstructionLightVFX[1];                 // 0x27C0
        tMarkerInfo m_aHeadLightLargeInfo[6];                           // 0x27C4
        tMarkerInfo m_aHeadLightSmallInfo[4];                           // 0x27DC
        tMarkerInfo m_aBreakLightInfo[4];                               // 0x27EC
        tMarkerInfo m_aTailLightInfo[4];                                // 0x27FC
        tMarkerInfo m_aReverseLightInfo[4];                             // 0x280C
        tMarkerInfo m_aPoliceLightRedInfo[4];                           // 0x281C
        tMarkerInfo m_PoliceHoodLightFrontInfo[3];                      // 0x282C
        tMarkerInfo m_PoliceHoodLightBackInfo[3];                       // 0x2838
        tMarkerInfo m_aPoliceLightBlueInfo[4];                          // 0x2844
        tMarkerInfo m_aConstructionLightInfo[1];                        // 0x2854
        tMarkerInfo m_RearWeaponMarkerInfo;                             // 0x2858
        VFX::cAfterlightRounded *m_pHeadlight[2];                       // 0x285C
        bool m_bExhaustActive;                                          // 0x2864
        bool m_bLightsOn;                                               // 0x2865
        bool m_bPoliceLightsOn;                                         // 0x2866
        bool m_bVehicleLightsActivated;                                 // 0x2867
        bool m_bPoliceLightsActivated;                                  // 0x2868
        unsigned char m_unmodelled2869[0x2894 - 0x2869];
        bool m_bMustStop;
        unsigned char m_unmodelled2895[0x28C0 - 0x2895];

        CD2_LAYOUT_CHECKS(cLandVehicle,
            CD2_SIZE(cLandVehicle, 0x28C0)
            CD2_OFFSET(cLandVehicle, m_DamageEffect, 0x1B58)
            CD2_OFFSET(cLandVehicle, m_LastUpdateTimestamp, 0x26E0)
            CD2_OFFSET(cLandVehicle, m_apHeadLightLargeVFX, 0x2730)
            CD2_OFFSET(cLandVehicle, m_apReverseLightVFX, 0x2778)
            CD2_OFFSET(cLandVehicle, m_aHeadLightLargeInfo, 0x27C4)
            CD2_OFFSET(cLandVehicle, m_aReverseLightInfo, 0x280C)
            CD2_OFFSET(cLandVehicle, m_pHeadlight, 0x285C)
            CD2_OFFSET(cLandVehicle, m_bLightsOn, 0x2865)
            CD2_OFFSET(cLandVehicle, m_bVehicleLightsActivated, 0x2867)
            CD2_OFFSET(cLandVehicle, m_bMustStop, 0x2894)
            CD2_OFFSET(cLandVehicle, m_pVehicleInstance, 0x1DA4))
    };
}

#endif
