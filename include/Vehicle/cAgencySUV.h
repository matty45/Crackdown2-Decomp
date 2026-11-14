#include "gom/object_prototype.h"
#include "rws/attributes.h"
// Vehicle::cAgencySUV (Crackdown 2): base cAgencyCar (RuffKing; CD2 inheritance registrar 0x82FEC170). Fields not modelled.
// StaticCreateClass (0x826FBC38) builds cClass(0x12060, "cAgencySUV", 0x30C0); 0x30C0 is the size its registrar gives.
#ifndef VEHICLE_CAGENCYSUV_H
#define VEHICLE_CAGENCYSUV_H

#include "fun_runtime/class.h"
#include "cd2/layout.h"
#include "Vehicle/cAgencyCar.h"

namespace Vehicle
{
    class cAgencySUV : public cAgencyCar
    {
    public:
        // CD2 0x826FBA68: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 spawning initializer 0x82FEC228 names placement factory 0x826fba78.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 placement factory forwards only this.
        cAgencySUV();                                     // CD2 0x826FBCD8
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcAgencySUVClass;
        static Fun_Runtime::cClass &StaticCreateClass();

        // Registered-class table 0x82138934: slot 0 (0x826FB958) and slot 1 (0x826FB968).
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;

        // CD2: cAgencySUV's own virtuals. Each slot below holds, in this class's CD2 vtable 0x82138178, an address its
        // base's table does not hold there, so the class overrides it; names and signatures are the bases'. The
        // destructor slot holds cCar's folded copy: the class declares no destructor.
        virtual void Slot23();                                  // 23: 0x826FBF40
        virtual Fun_Runtime::RetVal TermForReuse();             // 39: 0x826FBDA8
        virtual void vf85();                                    // 85: 0x826FBDF0
        virtual void ReplicateInitialFields();                  // cReplicatedClass 8: 0x826FC570
        virtual void ReplicateFields();                         // cReplicatedClass 9: 0x826FC5B0
        virtual unsigned int GetMaxReplicatedFields() const;    // cReplicatedClass 23: 0x82889198

    private:
        // RuffKing's members (0x2FB0 and 0x2FB4 there).
        float m_fChargeTimer;                                   // 0x30B0
        unsigned char m_nASUVFlags;                             // 0x30B4

        CD2_LAYOUT_CHECKS(cAgencySUV,
            CD2_SIZE(cAgencySUV, 0x30C0)
            CD2_OFFSET(cAgencySUV, m_fChargeTimer, 0x30B0)
            CD2_OFFSET(cAgencySUV, m_nASUVFlags, 0x30B4))
    };
}

#endif // VEHICLE_CAGENCYSUV_H
