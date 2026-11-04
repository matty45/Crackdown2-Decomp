// AI::cVehicleCollectionBehaviour (Crackdown 2): STAND-IN. Evidence: SpawnFromPrototype (0x824D68B8) calls cPilotBase's constructor (0x824D32E0), installs
// the class vtables and initialises the fields below (names ours); the size is its registrar's.
#ifndef AI_CVEHICLECOLLECTIONBEHAVIOUR_H
#define AI_CVEHICLECOLLECTIONBEHAVIOUR_H

#include "AI/cPilotBase.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"
#include "fun_runtime/vec3.h"
#include "fun_runtime/safedeletablepointer.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cVehicleCollectionBehaviour : public cPilotBase
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcVehicleCollectionBehaviourClass;

    private:
        Fun_Runtime::Vec3 m_vUnknown140; // 0x140
        Fun_Runtime::cSafeDeletablePointer<cNonGameBase> m_pUnknown150; // 0x150

    public:
        // __forceinline: CD2 inlines this constructor into SpawnFromPrototype (docs/matching-notes.md, "Inlining").
        __forceinline cVehicleCollectionBehaviour() {}
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

        CD2_LAYOUT_CHECKS(cVehicleCollectionBehaviour,
            CD2_SIZE(cVehicleCollectionBehaviour, 0x160)
            CD2_OFFSET(cVehicleCollectionBehaviour, m_vUnknown140, 0x140))
    };
}

#endif

