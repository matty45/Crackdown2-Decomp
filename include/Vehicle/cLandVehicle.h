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

namespace PHYSICS { class cCustomVehicleInstance; }

namespace Vehicle
{
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

    private:
        unsigned char m_unmodelled1740[0x1DA4 - 0x1740];
        PHYSICS::cCustomVehicleInstance *m_pVehicleInstance;
        unsigned char m_unmodelled1DA8[0x2894 - 0x1DA8];
        bool m_bMustStop;
        unsigned char m_unmodelled2895[0x28C0 - 0x2895];

        CD2_LAYOUT_CHECKS(cLandVehicle,
            CD2_SIZE(cLandVehicle, 0x28C0)
            CD2_OFFSET(cLandVehicle, m_bMustStop, 0x2894)
            CD2_OFFSET(cLandVehicle, m_pVehicleInstance, 0x1DA4))
    };
}

#endif
