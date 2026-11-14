// Vehicle::cVehicle (Crackdown 2): the base of every vehicle. Bases from RuffKing, confirmed by CD2's constructor
// (0x826CCD70) and destructor (0x826CE0E8), which call cNetDynamicBody's (0x82687ED0, 0x82687FE8) and install the same
// subobject tables as cProp: cNetDynamicBody's at 0..0x510, cExplosionCallback at 0x7A0, cDynamicObstacleOwner at 0x7A4
// and cSatchelChargeTarget at 0x7AC. Size 0x1740 (StaticCreateClass, registrar). Primary table 0x82015B40: 442 slots,
// 314..441 added here.
//
// Own virtuals: names are given only where the slot's body lines up with RuffKing's declaration order. CD2 slots 354..360
// match RuffKing's RetRoofCover..RetTheoreticalMaxMPH (three float getters, IsAgencyVehicle returning false at 356,
// IsApproxStationary calling the speed virtual at 357); 399..429 match RetNumberOfOccupants..HandleTryToEnterInteract-
// PermissionQuery (422, the four-argument IsNearTurret, calls 421 with the prototype's tolerances). The other slots keep
// their index as a placeholder name until their bodies are identified.
//
// Instance fields: only those a matched function uses are declared; the rest is unmodelled storage. Members the
// constructor and destructor reveal, in RuffKing's order (RuffKing names, CD2 offsets): m_VehicleAudio 0x7D0,
// m_Msg_Data_Modified 0x8F4, m_apComponentFrames[122] 0x8FC (8-byte frames), m_pVehicleController 0xD08, an object
// with its own destructor at 0xD5C, m_pExplosionInstigator 0x10E0, m_pExplosionAttacker 0x10F0, a listener at 0x1108,
// m_Msg_Vehicle_Controls 0x1128, m_VehicleSeats 0x1180, m_VehicleSeatData[6] 0x11B0 (0x5C bytes each),
// m_VehicleTurrets 0x1410 and a string at 0x15C4 that RuffKing does not have.
#ifndef VEHICLE_CVEHICLE_H
#define VEHICLE_CVEHICLE_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "gom/object_prototype.h"
#include "PHYSICS/cNetDynamicBody.h"
#include "ExplosionManager/cExplosionCallback.h"
#include "AI/cDynamicObstacleOwner.h"
#include "Equip/cSatchelChargeTarget.h"
#include "fun_runtime/vectorip.h"
#include "fun_runtime/stringc.h"
#include "Vehicle/cVehicleTurret.h"
#include "PHYSICS/cBuoyancyAction.h"

namespace VFX { class cGlobalLight; }
namespace PHYSICS { class cDynamicBodyInteractionData; }
namespace Damage { class cVehicleDamageManager; }

namespace Vehicle
{
    class cVehicleSeat;

    // RuffKing's vehicle kinds (its PDB values); cLandVehicle's FullySubmergedEvent (0x826C30B0) keeps the engine of
    // eVT_SUV running.
    enum eVehicleType
    {
        eVT_CAR = 0,
        eVT_VAN,
        eVT_SUV,
        eVT_TRUCK,
        eVT_BOAT,
        eVT_APC,
        eVT_BIKE,
    };

    // RuffKing's engine states; CD2's StartEngine stores 1 and StopEngine tests 1 and 2 before storing 3.
    enum etEngineStatus
    {
        eENG_OFF = 0,
        eENG_STARTING,
        eENG_RUNNING,
        eENG_STOPPING,
        eENG_BROKEN,
    };

    // RuffKing's light kinds; cLandVehicle's TurnOnVehicleLights (0x826C5268) passes 0, 1 and 2 for its large and
    // small headlights and tail lights, as RuffKing's does.
    enum eVehicleLightType
    {
        eVLT_Headlight_Large = 0,
        eVLT_Headlight_Small,
        eVLT_TailLight,
        eVLT_BreakLight,
        eVLT_ReverseLight,
        eVLT_PoliceLightRed,
        eVLT_PoliceLightBlue,
        eVLT_ConstructionLight,
        eVLT_SpotLight,
        eVLT_WarningLight,
        eVLT_Max,
    };

    class cVehicle : public PHYSICS::cNetDynamicBody, public ExplosionManager::cExplosionCallback,
        public AI::cDynamicObstacleOwner, public Equip::cSatchelChargeTarget
    {
    public:
        // Name, base and size (0x350, as RuffKing's static_assert) from RuffKing; CD2's MakeNew (0x826CC708) allocates
        // 0x350 bytes. Its constructor (0x826D95B8) initializes RuffKing's fields at their offsets from m_sProfileName
        // (0x280) to m_nColourCycleMax (0x318); from there CD2 has one more word, so m_strAudioVehicleType is at 0x334.
        // The fields are not modelled yet.
        class cVehiclePrototype : public PHYSICS::cDynamicBody::cDynamicBodyPrototype
        {
        public:
            cVehiclePrototype(const RWS::CAttributePacket &);   // CD2 0x826D95B8
            virtual ~cVehiclePrototype();                       // CD2 0x826D9730 (derived deleting destructors call it)

        private:
            unsigned char m_unmodelled280[0x2B8 - 0x280];
        public:
            eVehicleType m_eVehicleType;                    // 0x2B8 (RuffKing's name and offset)
        private:
            unsigned char m_unmodelled2BC[0x2C4 - 0x2BC];
        public:
            // RuffKing names and offsets; CD2's IsNearTurret (0x826D79B8) passes them.
            float m_VehicleSeatEntranceAngle;               // 0x2C4
            float m_VehicleSeatEntranceXZDistTolerance;     // 0x2C8
        private:
            unsigned char m_unmodelled2CC[0x350 - 0x2CC];

            // CD2: cVehiclePrototype's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
            // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        public:
            virtual Fun_Runtime::RetVal Init(RWS::CAttributePacket const &); // 5: 0x82683680
        private:
            CD2_LAYOUT_CHECKS(cVehiclePrototype,
                CD2_SIZE(cVehiclePrototype, 0x350)
                CD2_OFFSET(cVehiclePrototype, m_eVehicleType, 0x2B8)
                CD2_OFFSET(cVehiclePrototype, m_VehicleSeatEntranceAngle, 0x2C4)
                CD2_OFFSET(cVehiclePrototype, m_VehicleSeatEntranceXZDistTolerance, 0x2C8))
        };

        // CD2 placement factory 0x826CC770 forwards only this.
        cVehicle();                     // CD2 0x826CCD70
        virtual ~cVehicle();            // CD2 0x826CE0E8
        // Registered-class table 0x82135414: slot 0 (0x826CC6F8).
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826CC760: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FE9A28 names placement factory 0x826cc770.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x826CC860 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcVehicleClass;
        // CD2 0x826CC708, registered by the class-factory registrar (0x82FE99D8).
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x826CC798, registered as the script method "SetIsBeingHiJackedByAI".
        void SetIsBeingHiJackedByAI(bool bHiJacked);

        // CD2 slot 197 reads the reference-named 16-bit collision-system group.
        virtual unsigned short RetCollisionSystemGroup();
        // CD2 script method 0x826D5008; counts the inline pointer vector.
        int RetNumberOfSeats();
        // RuffKing's inline count; CD2's RetPtrPassenger (0x826D4FC8) compares it signed.
        int RetNumberofVehicleSeats() const { return m_VehicleSeats.size(); }
        // RuffKing's (out of line there); CD2 inlines it into HandleTryToCloseAlterantiveDoorPermissionQuery.
        cVehicleSeat *RetVehicleSeat(int nSeat)
        {
            if (nSeat < 0 || RetNumberofVehicleSeats() <= nSeat)
                return 0;
            return m_VehicleSeats[nSeat];
        }
        // RuffKing's; CD2 0x826D6F48.
        unsigned int RetSwapSeat(unsigned int nSeat);
        // CD2 script methods "RetPtrPassenger" (0x826D4FC8; RuffKing's RetPassenger) and "IsSeatOccupied" (0x826D6940).
        CHARACTER::cCharacter *RetPtrPassenger(int nSeat);
        bool IsSeatOccupied(unsigned int nSeat);
        // CD2 0x826D6990 (11 callers) is RuffKing's IsSeatOccupied body (seat index from 0, same signature); CD2's
        // script registration gives that name to the 1-based form above, so this name is ours.
        bool IsSeatIndexOccupied(unsigned int nSeat);
        // RuffKing's; CD2 0x826D6B98 (HandleTryToCloseDoorInteractionPermissionQuery calls it first, as RuffKing's).
        bool CanSeatDoorBeClosed(unsigned int nSeat);
        // CD2 script method "Detonate" (0x826D93D0) tail-calls BlowUp (0x823169C8) with RuffKing's argument order.
        void Detonate(CHARACTER::cCharacterInterface *pAttacker);
        // RuffKing's name and parameter name (CD2 0x826D51B0): whether pObject occupies one of the seats.
        // RetCollisionLayer (0x826D4DB0) passes the local player object itself.
        bool IsInVehicle(cNonGameBase *pObject);
        // RuffKing's; CD2 0x826D5020 returns the turret slot only while it holds a turret.
        cVehicleTurret *RetVehicleTurret(int nTurret);
        void BlowUp(cGameBase *pInstigator, CHARACTER::cCharacterInterface *pAttacker, unsigned char nActivationType,
            bool bDetonateExplosive);

        // Interface overrides RuffKing declares; CD2 installs cVehicle's own tables at 0x7A0 (0x8213473C), 0x7A4
        // (0x82136BC8) and 0x7AC (0x821354E0).
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        virtual void CreateDynamicObstacle();
        virtual unsigned char GetDynamicObstacleInput();
        // CD2 cIgnitable table slot 5 at 0x82135440, body 0x826D1B68; RuffKing names the override.
        virtual float RetFireRadius() const;
        // cScriptHost slot 4 at 0x821353FC (+0x1C), body 0x826CE500.
        virtual const char *RetName() const;
        virtual cGameBase *RetSatchelAttachObject();
        virtual void OnAttachSatchelCharge(Equip::cCWSatchelCharge *);
        virtual void OnDetachSatchelCharge(Equip::cCWSatchelCharge *);

        // Primary slots 314..441: cVehicle's own virtuals (see above).
        virtual void UpdateNetworkInterpolation(float dT); virtual void UpdateCollisionLayer(); virtual void vf316(); virtual void vf317(); virtual void vf318(); virtual void vf319();
        virtual void vf320(); virtual void vf321(); virtual void vf322(); virtual void vf323(); virtual void vf324(); virtual void vf325();
        virtual bool IsReversing(); virtual bool IsHandbrakeOn(); virtual void vf328(); virtual void vf329(); virtual void vf330(); virtual void vf331();
        virtual void vf332(); virtual void vf333(); virtual void vf334(); virtual void vf335(); virtual void vf336(); virtual void vf337();
        virtual void vf338(); virtual void vf339(); virtual void vf340(); virtual void vf341(); virtual void vf342(); virtual void vf343();
        virtual void SetEngineState(const etEngineStatus eNewState); virtual void StartEngine(); virtual void StopEngine(); virtual bool IsFunctionallyDamaged(); virtual void vf348(); virtual bool LocateParts(const char **, unsigned short);
        virtual bool CreateParts(const char **, unsigned short); virtual void vf351(); virtual void vf352(); virtual void SetSteeringAngle(float); virtual float RetRoofCover(); virtual void vf355();
        virtual void vf356(); virtual void vf357(); virtual float RetSteeringAngle(); virtual float RetSteeringMaxAngle();
        virtual float RetTheoreticalMaxMPH();   // slot 360, CD2 0x826CC788
        virtual void vf361(); virtual void vf362(); virtual void SetEngineDamage(float); virtual float RetEngineDamage(); virtual void vf365(); virtual void vf366();
        virtual void vf367(); virtual void vf368(); virtual void vf369(); virtual void SetPhysicsLOD(unsigned char nNewLOD); virtual void EventPhysicsLODChange(unsigned char, unsigned char); virtual bool IsOnGround();
        virtual float RetNetworkDoorOpenCloseSpeed(unsigned char nSeatIdx); virtual void vf374(); virtual void vf375(); virtual void vf376(); virtual bool CheckForReplicationActivation(unsigned int *nRetCode); virtual void vf378();
        virtual unsigned char GetForceOpenMask(); virtual void vf380(); virtual void vf381(); virtual bool IsLightActive(VFX::cGlobalLight *pLight, unsigned char nLightType, unsigned char nIndex); virtual void vf383(); virtual void vf384();
        virtual void vf385(); virtual Damage::cVehicleDamageManager *RetVehicleDamageManager(); virtual void vf387(); virtual void vf388(); virtual PHYSICS::cNetDynamicBody::eArbitrationResult ArbitrateOwnership(unsigned char nNodeID, unsigned int TimeStamp); virtual void vf390();
        virtual void vf391(); virtual void vf392(); virtual void vf393(); virtual void vf394(); virtual void vf395(); virtual void vf396();
        virtual void vf397(); virtual void vf398(); virtual unsigned int RetNumberOfOccupants(); virtual unsigned int RetSeatsInUse(); virtual void vf401(); virtual void vf402();
        virtual void vf403(); virtual bool IsDrivenByAI(); virtual void vf405(); virtual bool IsTyreInflated(unsigned char nWheel); virtual bool AllTyresInflated(); virtual void ActivatePoliceLights(bool bActivate);
        virtual bool CanActivatePoliceLights(); virtual bool IsAPoliceVehicle(); virtual bool RetPoliceLightsActivated(); virtual void vf412(); virtual void vf413(); virtual void vf414();
        virtual void vf415(); virtual bool MustStop(); virtual void SetMustStop(bool); virtual bool IsOkToInteract();
        // Slots 419 (six arguments) and 420 (four), RuffKing's IsNearDoor pair; declared in reverse, as IsNearTurret.
        virtual bool IsNearDoor(CHARACTER::cCharacter *pCharacter, unsigned int nSeat, float &fDist, bool &bMirrored);
        virtual bool IsNearDoor(CHARACTER::cCharacter *pCharacter, unsigned int nSeat, float fAngleTolerance,
            float fDistanceTolerance, float &fDist, bool &bMirrored);
        
        // Slots 421 (six arguments) and 422 (four); CD2's four-argument form (0x826D79B8) calls slot 421 with the
        // prototype's entrance tolerances. MSVC places overloaded virtuals in reverse declaration order, so the
        // four-argument form is declared first (declared the other way round, the call goes to 0x698).
        virtual bool IsNearTurret(CHARACTER::cCharacter *pCharacter, unsigned int nTurret, char &nAttachPoint, float &fDist);
        virtual bool IsNearTurret(CHARACTER::cCharacter *pCharacter, unsigned int nTurret, float fAngleTolerance, float fDistanceTolerance, char &nAttachPoint, float &fDist);
        virtual void HandleTryToSwapSeatsInteractionPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); virtual void HandleTryToCloseAlterantiveDoorPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); virtual void HandleTryToCloseDoorInteractionPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); virtual void HanldTryToEjectInteractPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult);
        virtual void HandleTryToExitInteractPermisiionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); virtual void HandleTryToEnterInteractPermissionQuery(PHYSICS::cDynamicBodyInteractionData *pInteractionData, cNonGameBase *pNonGameBase, bool &bInteractionResult); virtual void vf429(); virtual void vf430(); virtual void vf431(); virtual void vf432();
        virtual void vf433(); virtual void vf434(); virtual void vf435(); virtual void vf436(); virtual void vf437(); virtual void vf438();
        virtual void vf439(); virtual void vf440(); virtual void vf441();

    private:
        unsigned char m_unmodelled7B4[0xCE9 - 0x7B4];
        // RuffKing names; CD2 offsets from StopEngine (0x826D2070), GetForceOpenMask (0x826DAA60), SetPhysicsLOD
        // (0x826DA0D8) and StartEngine (0x826D2028).
        bool m_bEngineShutdown;                         // 0xCE9
        unsigned char m_unmodelledCEA[0xCEC - 0xCEA];
        // RuffKing's name, three bytes after m_bEngineShutdown as there; RetCollidableQuality (0x826D93F0) tests it.
        bool m_bPlayerInteracting;                      // 0xCEC
        unsigned char m_unmodelledCED[0x1110 - 0xCED];
    protected:
        // RuffKing's name; cLandVehicle's IsFunctionallyDamaged (0x826C25D8) tests it between the engine state and the
        // wheel damage, as RuffKing's does.
        bool m_bBlownUp;                                // 0x1110
    private:
        unsigned char m_unmodelled1111[0x1115 - 0x1111];
        bool m_ForceOpen[4];                            // 0x1115
        unsigned char m_nJuggleLastNode;                // 0x1119
        unsigned char m_nJuggleCount;                   // 0x111A
        unsigned char m_nJuggleNodeStatus;              // 0x111B
        unsigned char m_nPhysicsLOD;                    // 0x111C
        etEngineStatus m_eEngineState;                  // 0x1120
        float m_fEngineStateTime;                       // 0x1124
        unsigned char m_unmodelled1128[0x115C - 0x1128];
        float m_fEngineHazeTimer;                       // 0x115C
        unsigned char m_unmodelled1160[0x1180 - 0x1160];
        Fun_Runtime::cVectorip<cVehicleSeat *, 6> m_VehicleSeats;
        unsigned char m_unmodelled11B0[0x1410 - 0x11B0];
        // RuffKing's name and type; CD2's RetVehicleTurret (0x826D5020).
        Fun_Runtime::cVectorip<cVehicleTurret, 3> m_VehicleTurrets;   // 0x1410
        unsigned char m_unmodelled15C0[0x15C4 - 0x15C0];
        // Not in RuffKing; CD2's RetName override (0x826CE500, cScriptHost slot 4) returns its c_str(). Name ours.
        Fun_Runtime::cStringc m_strName;                // 0x15C4
        unsigned char m_unmodelled15E0[0x15E6 - 0x15E0];
        unsigned short m_nSystemGroup;
        unsigned char m_unmodelled15E8[0x15F7 - 0x15E8];
        bool m_bIsBeingHiJackedByAI;                    // 0x15F7
        unsigned char m_unmodelled15F8[0x15F9 - 0x15F8];
        // RuffKing's name; IsSeatDoorLocked returns it whatever the seat (inlined by CD2's IsOkToInteract).
        bool m_bDoorLocked;                             // 0x15F9
        unsigned char m_unmodelled15FA[0x1740 - 0x15FA];

        // CD2: cVehicle's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x826CDBA8
        virtual bool EnterPhysicalState(); // 7: 0x826D2618
        virtual void Slot13(); // 13: 0x826CE428
        virtual void Slot14(); // 14: 0x826D1DB0
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x826CD290
        virtual void Slot23(); // 23: 0x822D2598
        virtual void Slot24(); // 24: 0x822FAE98
        virtual void LeavePhysicalState(); // 27: 0x826D2890
        virtual void Slot30(); // 30: 0x826D2610
        virtual bool EnterRenderableState(eResourcesType); // 31: 0x826D2A18
        virtual Fun_Runtime::RetVal Slot37(); // 37: 0x822ED9B8
        virtual Fun_Runtime::RetVal Reinitialise(GOM::cSpawner const *); // 38: 0x826CD740
        virtual Fun_Runtime::RetVal TermForReuse(); // 39: 0x82303020
        virtual void Slot61(); // 60: 0x826CD9F8
        virtual void Slot62(); // 61: 0x8272C3E8
        virtual void vf72(); // 72: 0x826D0C18
        virtual void vf76(); // 76: 0x823BA1C0
        virtual void vf86(); // 86: 0x826D02C0
        virtual void vf87(); // 87: 0x823B7280
        virtual void vf91(); // 91: 0x826D0910
        virtual void vf92(); // 92: 0x821F2308
        virtual void vf93(); // 93: 0x821D71C0
        virtual void vf96(); // 96: 0x826D1748
        virtual void vf114(); // 114: 0x822EFF00
        virtual void vf132(); // 132: 0x826DAA30
        virtual void vf140(); // 140: 0x826D3098
        virtual void vf142(); // 142: 0x822849D0
        virtual void vf145(); // 145: 0x822849F8
        virtual void vf153(); // 153: 0x821D0CD0
        virtual void vf154(); // 154: 0x826AB0F0
        virtual hkCollidableQualityType RetCollidableQuality(hkMotion::MotionType); // 156: 0x826D93F0
        virtual void vf157(); // 157: 0x826D4948
        virtual void vf163(); // 163: 0x822F2B50
        virtual void vf164(); // 164: 0x8226AB60
        virtual void vf167(); // 167: 0x826D9308
        virtual void vf183(); // 183: 0x8228E650
        virtual unsigned char RetCollisionLayer(); // 196: 0x826D4DB0
        virtual void vf211(); // 211: 0x822B2E88
        virtual void vf212(); // 212: 0x8229C2B8
        virtual void vf213(); // 213: 0x826DA4B0
        virtual void vf215(); // 215: 0x826DA108
        virtual void vf217(); // 217: 0x826CFEC8
        virtual float RetFwdMPH(); // 240: 0x826B8918
        virtual void vf241(); // 241: 0x826AB178
        virtual void vf242(); // 242: 0x826AB0E8
        virtual void vf243(); // 243: 0x822AEAA8
        virtual void vf254(); // 254: 0x826D4A40
        virtual void vf258(); // 258: 0x823B0A90
        virtual void vf259(); // 259: 0x821FF1F8
        virtual void vf260(); // 260: 0x826DD358
        virtual void vf261(); // 261: 0x826DD370
        virtual void vf262(); // 262: 0x826DD3C8
        virtual void vf263(); // 263: 0x826D7EB8
        virtual void vf264(); // 264: 0x826D7FA0
        virtual void vf265(); // 265: 0x826D86A0
        virtual void vf266(); // 266: 0x826D20E8
        virtual void EnterGhostState(); // 271: 0x826D4990
        virtual void vf280(); // 280: 0x826DA608
        virtual void vf281(); // 281: 0x826DA678
        virtual void vf282(); // 282: 0x826AB170
        virtual void vf283(); // 283: 0x826DECE0
        virtual void vf288(); // 288: 0x82311E28
        virtual void vf290(); // 290: 0x826D9408
        virtual void vf295(); // 295: 0x826D2F68
        virtual void vf296(); // 296: 0x826D2CF8
        virtual void vf298(); // 298: 0x8288FB78
        virtual void EndInterpolationOptional(); // 304: 0x826DAA40
        virtual void SetDeletingReason(char); // 309: 0x826AB150
        virtual char GetDeletingReason(); // 310: 0x826AB158
        virtual void HandleEvents(RWS::CMsg &); // CEventHandler 5: 0x82245448
        virtual void ActivateDynamicObstacle(); // cDynamicObstacleOwner 2: 0x82405AA8
        virtual void SetNetRole(etNetRole); // cNetRoleObject 1: 0x826DDB08
        virtual void CalculateRelevancy(int); // cReplicatedClass 2: 0x826DC898
        virtual void CalculateLOD(int); // cReplicatedClass 3: 0x826BD6C0
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x82395FB0
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x826BD6C8
        virtual void ReplicateHeaderData(); // cReplicatedClass 10: 0x826DB570
        virtual void SetPingedFieldStatesForNode(unsigned char); // cReplicatedClass 20: 0x826CE5A0
        virtual SNetworkHeader::etNetworkDataType GetReplicatedObjectType() const; // cReplicatedClass 22: 0x8288F788
        virtual unsigned int GetMaxReplicatedFields() const; // cReplicatedClass 23: 0x82889078
        virtual Fun_Runtime::cScriptTypeRegistration const * RetScriptTypeRegistration() const; // cSafeDeletable 1: 0x826AB0D8
    protected:
        virtual Fun_Runtime::Vec3 RetIgnitablePosition() const; // cIgnitable 4: 0x826D1A18
        virtual bool CanDoFireDamage() const; // cIgnitable 6: 0x827E56A8
        virtual void EventTriggerStartFire(CHARACTER::cCharacter *); // cIgnitable 10: 0x826D17E8
        virtual void EventTriggerEndFire(); // cIgnitable 12: 0x826D1800
    private:
        // CD2: cVehicle's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
    protected:
        // RuffKing's marker reference of one light (4 bytes; cLandVehicle's arrays of them are at RuffKing's offsets).
        struct tMarkerInfo
        {
            unsigned char nComponentId;
            unsigned char nIndex;
            unsigned char nComponentId2;
            unsigned char nIndex2;
        };
        // RuffKing's inline helper (its COMDAT copy 0x828CF4B0); CD2 inlines it into cLandVehicle::CanTurnOnExhaustFumes
        // (0x826C2BB0).
        bool IsEngineActive() { return m_eEngineState != eENG_OFF && m_eEngineState != eENG_BROKEN; }
        // RuffKing declares it (no out-of-line copy).
        unsigned char RetPhysicsLOD() { return m_nPhysicsLOD; }
        // RuffKing's helpers (out of line there). CD2 calls IsUpRight (0x823A1B58), IsDoorAngleOk (0x822FD2A8) and
        // IsInFadeToDeleteFinalStage (0x8239FD30); it inlines IsSufficientlyInWater and IsSeatDoorLocked into both
        // cVehicle's and cHelicopter's IsOkToInteract and has no copy of them.
        bool IsUpRight();
        bool IsDoorAngleOk();
    public:
        bool IsInFadeToDeleteFinalStage();
        bool IsSufficientlyInWater() { return IsInWater() && m_pBuoyancyAction && m_pBuoyancyAction->m_bInWater; }
        bool IsSeatDoorLocked(unsigned int) { return m_bDoorLocked; }
    protected:
        // RuffKing's light helpers; cLandVehicle's light virtuals call CD2 0x82269110 and 0x821D1508 with these
        // arguments.
        void AddVehicleLight(VFX::cGlobalLight **paLight, tMarkerInfo *aInfo, unsigned char nCount, char nType); // CD2 0x826DDE40
        void TurnOnVehicleLight(VFX::cGlobalLight **paLight, tMarkerInfo *aInfo, unsigned char nCount, eVehicleLightType eType);
        void TurnOffVehicleLights(VFX::cGlobalLight **paLight, tMarkerInfo *aInfo, unsigned char nCount);
        // Slot 26: CD2's cVehicle table holds 0x826DA5B8, which cProp's table shares (identical bodies folded).
        virtual void UpdateRenderMatrix();
    private:
        CD2_LAYOUT_CHECKS(cVehicle,
            CD2_SIZE(cVehicle, 0x1740)
            CD2_OFFSET(cVehicle, m_bIsBeingHiJackedByAI, 0x15F7)
            CD2_OFFSET(cVehicle, m_bDoorLocked, 0x15F9)
            CD2_OFFSET(cVehicle, m_VehicleSeats, 0x1180)
            CD2_OFFSET(cVehicle, m_VehicleTurrets, 0x1410)
            CD2_OFFSET(cVehicle, m_strName, 0x15C4)
            CD2_OFFSET(cVehicle, m_bEngineShutdown, 0xCE9)
            CD2_OFFSET(cVehicle, m_bPlayerInteracting, 0xCEC)
            CD2_OFFSET(cVehicle, m_bBlownUp, 0x1110)
            CD2_OFFSET(cVehicle, m_ForceOpen, 0x1115)
            CD2_OFFSET(cVehicle, m_nPhysicsLOD, 0x111C)
            CD2_OFFSET(cVehicle, m_eEngineState, 0x1120)
            CD2_OFFSET(cVehicle, m_fEngineHazeTimer, 0x115C)
            CD2_OFFSET(cVehicle, m_nSystemGroup, 0x15E6))
    };
}

#endif // VEHICLE_CVEHICLE_H
