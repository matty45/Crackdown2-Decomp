#include "Equip/cGrenade.h"
#include "gom/object_prototype.h"
#include "rws/attributes.h"
// unknown::cBoostPack (Crackdown 2): STAND-IN; derived storage is not modelled yet.
// Base cGrenade: CD2's inheritance registrar names it, and the destructor 0x8260AED8 calls cGrenade's (0x8261E460).
// StaticCreateClass (0x8260ADA0) builds cClass(0x10141, "cBoostPack", 0x9D0); 0x9D0 is the size its registrar gives.
#ifndef UNKNOWN_CBOOSTPACK_H
#define UNKNOWN_CBOOSTPACK_H

#include "fun_runtime/class.h"

namespace unknown
{
    class cBoostPack : public Equip::cGrenade
    {
    public:
        // CD2 table 0x8211FD38 places GetField9C4 at slot 435. Names/signatures of these slots remain unrecovered.
        virtual void vf427(); // primary slot 427
        virtual void vf428(); // primary slot 428
        virtual void vf429(); // primary slot 429
        virtual void vf430(); // primary slot 430
        virtual void vf431(); // primary slot 431
        virtual void vf432(); // primary slot 432
        virtual void vf433(); // primary slot 433
        virtual void vf434(); // primary slot 434

        // Inline: CD2's placement factory (0x8260AC68) calls cGrenade's (0x8261E238) constructor, then stores this class's vptrs.
        __forceinline cBoostPack() : m_fField9C4(100.0f) {}
        // CD2 0x8260AD38: cScriptHost slot 1; descriptive method name is ours.
        virtual const Fun_Runtime::cScriptTypeRegistration *RetScriptTypeRegistration() const;
        // CD2 0x8260AC58: primary virtual slot 11 returns the registered class name.
        virtual const char *RetClassName() const;
        // CD2 0x8260AED8.
        virtual ~cBoostPack();
        // CD2 0x8260AD98: float getter at offset 0x9C4.
        virtual float GetField9C4() const;
        int m_nWord9C0; // 0x9C0
        float m_fField9C4; // 0x9C4
        // CD2 spawning initializer 0x82FCC368 names placement factory 0x8260ac68.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcBoostPackClass;
        static Fun_Runtime::cClass &StaticCreateClass();
        // CD2: cBoostPack's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual Fun_Runtime::RetVal Term(); // 6: 0x8260AE90
        virtual Fun_Runtime::RetVal Init(GOM::cSpawner const *); // 18: 0x8260B430
        virtual Fun_Runtime::cClass const & RetClass() const; // cBody 0: 0x8260B138
        virtual bool IsA(Fun_Runtime::cClass const &) const; // cBody 1: 0x8260B140
        virtual void ReplicateInitialFields(); // cReplicatedClass 8: 0x8261F5F0
        virtual void ReplicateFields(); // cReplicatedClass 9: 0x82396118

    public:
        // CD2 table 0x8211FD38 differs from cGrenade at these inherited slots.
        virtual void vf381(); // slot 381: 0x827E56A8
        virtual void vf410(); // slot 410: 0x8260B558
    };
}

#endif // UNKNOWN_CBOOSTPACK_H
