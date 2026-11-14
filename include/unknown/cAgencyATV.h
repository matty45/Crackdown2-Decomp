#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cAgencyATV (Crackdown 2): STAND-IN. Base Vehicle::cAgencyCar: CD2's inheritance registrar (0x82FEAC70) names
// it and the constructor (0x826E33A0) calls cAgencyCar's (0x826EC3C0) first. StaticCreateClass (0x826E3300) builds
// cClass(0x12065, "cAgencyATV", 0x31F0); 0x31F0 is the size its registrar gives. Neither reference build has the class;
// its own fields are not modelled.
#ifndef UNKNOWN_CAGENCYATV_H
#define UNKNOWN_CAGENCYATV_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"

namespace unknown
{
    class cAgencyATV : public Vehicle::cAgencyCar
    {
    public:
        // CD2 0x826E33A0; the placement factory (0x826E23D8) forwards only this.
        cAgencyATV();
        // CD2 0x826E2300: registered-class virtual slot 0 reads this class descriptor.
        virtual const Fun_Runtime::cClass &RetClass() const;
        // CD2 0x826E23C8: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEAD28 names placement factory 0x826e23d8.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencyATVClass;
        static Fun_Runtime::cClass &StaticCreateClass();

    private:
        unsigned char m_unmodelled30B0[0x31F0 - 0x30B0];

        CD2_LAYOUT_CHECKS(cAgencyATV,
            CD2_SIZE(cAgencyATV, 0x31F0))
    };
}

#endif // UNKNOWN_CAGENCYATV_H
