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

namespace Vehicle
{
    class cVehicleSeat;
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
            unsigned char m_unmodelled280[0x350 - 0x280];

            CD2_LAYOUT_CHECKS(cVehiclePrototype,
                CD2_SIZE(cVehiclePrototype, 0x350))
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

        // Interface overrides RuffKing declares; CD2 installs cVehicle's own tables at 0x7A0 (0x8213473C), 0x7A4
        // (0x82136BC8) and 0x7AC (0x821354E0).
        virtual void NotifyDetonation(cGameBase *, CHARACTER::cCharacterInterface *, unsigned char);
        virtual void CreateDynamicObstacle();
        virtual unsigned char GetDynamicObstacleInput();
        virtual cGameBase *RetSatchelAttachObject();
        virtual void OnAttachSatchelCharge(Equip::cCWSatchelCharge *);
        virtual void OnDetachSatchelCharge(Equip::cCWSatchelCharge *);

        // Primary slots 314..441: cVehicle's own virtuals (see above).
        virtual void vf314(); virtual void vf315(); virtual void vf316(); virtual void vf317(); virtual void vf318(); virtual void vf319();
        virtual void vf320(); virtual void vf321(); virtual void vf322(); virtual void vf323(); virtual void vf324(); virtual void vf325();
        virtual void vf326(); virtual void vf327(); virtual void vf328(); virtual void vf329(); virtual void vf330(); virtual void vf331();
        virtual void vf332(); virtual void vf333(); virtual void vf334(); virtual void vf335(); virtual void vf336(); virtual void vf337();
        virtual void vf338(); virtual void vf339(); virtual void vf340(); virtual void vf341(); virtual void vf342(); virtual void vf343();
        virtual void vf344(); virtual void vf345(); virtual void vf346(); virtual void vf347(); virtual void vf348(); virtual bool LocateParts(const char **, unsigned short);
        virtual bool CreateParts(const char **, unsigned short); virtual void vf351(); virtual void vf352(); virtual void vf353(); virtual void vf354(); virtual void vf355();
        virtual void vf356(); virtual void vf357(); virtual void vf358(); virtual void vf359();
        virtual float RetTheoreticalMaxMPH();   // slot 360, CD2 0x826CC788
        virtual void vf361(); virtual void vf362(); virtual void vf363(); virtual void vf364(); virtual void vf365(); virtual void vf366();
        virtual void vf367(); virtual void vf368(); virtual void vf369(); virtual void vf370(); virtual void vf371(); virtual void vf372();
        virtual void vf373(); virtual void vf374(); virtual void vf375(); virtual void vf376(); virtual void vf377(); virtual void vf378();
        virtual void vf379(); virtual void vf380(); virtual void vf381(); virtual void vf382(); virtual void vf383(); virtual void vf384();
        virtual void vf385(); virtual void vf386(); virtual void vf387(); virtual void vf388(); virtual void vf389(); virtual void vf390();
        virtual void vf391(); virtual void vf392(); virtual void vf393(); virtual void vf394(); virtual void vf395(); virtual void vf396();
        virtual void vf397(); virtual void vf398(); virtual void vf399(); virtual void vf400(); virtual void vf401(); virtual void vf402();
        virtual void vf403(); virtual void vf404(); virtual void vf405(); virtual void vf406(); virtual void vf407(); virtual void vf408();
        virtual void vf409(); virtual void vf410(); virtual void vf411(); virtual void vf412(); virtual void vf413(); virtual void vf414();
        virtual void vf415(); virtual bool MustStop(); virtual void SetMustStop(bool); virtual void vf418(); virtual void vf419(); virtual void vf420();
        virtual void vf421(); virtual void vf422(); virtual void vf423(); virtual void vf424(); virtual void vf425(); virtual void vf426();
        virtual void vf427(); virtual void vf428(); virtual void vf429(); virtual void vf430(); virtual void vf431(); virtual void vf432();
        virtual void vf433(); virtual void vf434(); virtual void vf435(); virtual void vf436(); virtual void vf437(); virtual void vf438();
        virtual void vf439(); virtual void vf440(); virtual void vf441();

    private:
        unsigned char m_unmodelled7B4[0x1180 - 0x7B4];
        Fun_Runtime::cVectorip<cVehicleSeat *, 6> m_VehicleSeats;
        unsigned char m_unmodelled11B0[0x15E6 - 0x11B0];
        unsigned short m_nSystemGroup;
        unsigned char m_unmodelled15E8[0x15F7 - 0x15E8];
        bool m_bIsBeingHiJackedByAI;                    // 0x15F7
        unsigned char m_unmodelled15F8[0x1740 - 0x15F8];

        CD2_LAYOUT_CHECKS(cVehicle,
            CD2_SIZE(cVehicle, 0x1740)
            CD2_OFFSET(cVehicle, m_bIsBeingHiJackedByAI, 0x15F7)
            CD2_OFFSET(cVehicle, m_VehicleSeats, 0x1180)
            CD2_OFFSET(cVehicle, m_nSystemGroup, 0x15E6))
    };
}

#endif // VEHICLE_CVEHICLE_H
