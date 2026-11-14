// Vehicle::cCar (Crackdown 2): base cWheelGroup (RuffKing), size 0x3070: its class-factory registrar (0x82FE7AE0)
// registers "cCar" with MakeNew (0x826B5D18) and size 0x3070. Fields not modelled.
#ifndef VEHICLE_CCAR_H
#define VEHICLE_CCAR_H

#include "rws/attributes.h"
#include "cd2/layout.h"
#include "fun_runtime/class.h"
#include "fun_runtime/retval.h"
#include "gom/object_prototype.h"
#include "Vehicle/cWheelGroup.h"

namespace Vehicle
{
    class cCar : public cWheelGroup
    {
    public:
        // Name, base and size (0x4B0) from RuffKing; CD2's MakeNew (0x826B5D18) allocates 0x4B0 bytes and calls the
        // constructor at 0x826B7BE0. Fields not modelled.
        class cCarPrototype : public cWheelGroup::cWheelGroupPrototype
        {
        public:
            cCarPrototype(const RWS::CAttributePacket &);       // CD2 0x826B7BE0
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);   // CD2 0x826B7CF8

        private:
            unsigned char m_unmodelled440[0x4B0 - 0x440];

            CD2_LAYOUT_CHECKS(cCarPrototype,
                CD2_SIZE(cCarPrototype, 0x4B0))
        };

        // CD2 0x826B5E30; the placement factory (0x826B5D80) forwards only this.
        cCar();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x826B5D98 creates the named runtime descriptor; 0x82FE7A50 initializes ms_pcCarClass from it.
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcCarClass;
        // Registered-class table 0x82134618: slot 0 (0x826B5CA8) and slot 1 (0x826B5CB8).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        // CD2 0x822E7068; the agency cars' deleting destructors call it.
        virtual ~cCar();

        // CD2: cCar's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
        // Primary table 0x8201A950 (495 slots).
        virtual Fun_Runtime::RetVal Term();                     // 6: 0x826B6880
        virtual bool EnterPhysicalState();                      // 7: 0x822963E0
        virtual void Slot13();                                  // 13: 0x826B6940
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);    // 18: 0x826B6038
        virtual void Slot23();                                  // 23: 0x826B6F40
        virtual void Slot24();                                  // 24: 0x826B6FA0
        // 27: 0x826B7538 is a tail call to cVehicle's (0x826D2890); cAgencySports's override calls cVehicle's
        // directly, so this one is inline. RuffKing names the slot LeavePhysicalState.
        virtual void LeavePhysicalState() { cVehicle::LeavePhysicalState(); }
        virtual Fun_Runtime::RetVal Slot37();                                  // 37: 0x826B6740
        virtual Fun_Runtime::RetVal Reinitialise(const GOM::cSpawner *);    // 38: 0x826B67A8
        virtual Fun_Runtime::RetVal TermForReuse();             // 39: 0x826B68E0
        virtual GOM::cPointOfInterest *RetPointOfInterest(int nPoint);                                   // 122: 0x826B7540
        virtual unsigned char RetNumPointsOfInterest();                                   // 123: 0x8230E310
        virtual void vf124();                                   // 124: 0x826B75B8
        virtual void vf125();                                   // 125: 0x821D0CE0
        virtual void vf126();                                   // 126: 0x8288FB78
        virtual void vf127();                                   // 127: 0x82294340
        virtual void vf140();                                   // 140: 0x826B6CE8
        virtual void vf322();                                   // 322: 0x826B6CB0
        virtual void vf323();                                   // 323: 0x826B6ED0
        virtual void vf334();                                   // 334: 0x826B70C0
        virtual void vf340();                                   // 340: 0x826B7030
        virtual void vf341();                                   // 341: 0x826B1C48
        virtual void vf365();                                   // 365: 0x826B6848
        virtual float RetNetworkDoorOpenCloseSpeed(unsigned char nSeatIdx);   // 373: 0x822AAD78
        virtual void vf375();                                   // 375: 0x82271DA0
        virtual void vf387();                                   // 387: 0x826AB2E0
        virtual void vf391();                                   // 391: 0x826B6808
        virtual void OverrideProfileParams();                   // 447: 0x8230AF78
        virtual bool SpawnExhaustVFX();                         // 468: 0x826B7868
        virtual void vf484();                                   // 484: 0x8230AA48
        virtual void vf485();                                   // 485: 0x82279DC0
        virtual void vf486();                                   // 486: 0x8230ACE0
        virtual void vf487();                                   // 487: 0x826B7100
        virtual void vf488();                                   // 488: 0x8228DAC0
        // Slots 489..494 are cCar's own virtuals; their bodies are not identified yet.
        virtual void vf489(); virtual void vf490(); virtual void vf491(); virtual void vf492(); virtual void vf493();
        virtual void vf494();
        virtual void ReplicateInitialFields();                  // cReplicatedClass 8: 0x826B6A40
        virtual void ReplicateFields();                         // cReplicatedClass 9: 0x826B6AC0
        virtual unsigned int GetMaxReplicatedFields() const;    // cReplicatedClass 23: 0x8288E2C0

    private:
        unsigned char m_unmodelled2A30[0x3070 - 0x2A30];

        CD2_LAYOUT_CHECKS(cCar,
            CD2_SIZE(cCar, 0x3070))
    };
}

#endif // VEHICLE_CCAR_H
