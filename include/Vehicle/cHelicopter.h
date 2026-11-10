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

namespace Vehicle
{
    class cHelicopter : public cVehicle
    {
    public:
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

    private:
        unsigned char m_unmodelled1740[0x1948 - 0x1740];

    public:
        cHeliPrototype *m_pHeliPrototype;                   // 0x1948 (RuffKing's name)

    private:
        unsigned char m_unmodelled194C[0x1AC0 - 0x194C];
        cPintleMount m_aTurrets[2];                         // 0x1AC0 (RuffKing's name and count)
        unsigned char m_unmodelled1D60[0x2DB0 - 0x1D60];

        CD2_LAYOUT_CHECKS(cHelicopter,
            CD2_SIZE(cHelicopter, 0x2DB0)
            CD2_OFFSET(cHelicopter, m_pHeliPrototype, 0x1948)
            CD2_OFFSET(cHelicopter, m_aTurrets, 0x1AC0))
    };
}

#endif
