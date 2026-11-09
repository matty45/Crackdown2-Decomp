// AI::cMissionCriticalProp (Crackdown 2): STAND-IN with cProp base, interactable flag and CD2 size 0xE40.
// Base Prop::cProp and member name follow RuffKing's header;
// RetClassName (0x8245AF38) is slot 11 of the vtable at 0x82102F88, as cNonGameBase's RetClassName.
#ifndef AI_CMISSIONCRITICALPROP_H
#define AI_CMISSIONCRITICALPROP_H

#include "gom/object_prototype.h"
#include "rws/attributes.h"
#include "Prop/cProp.h"

namespace AI
{
    class cMissionCriticalProp : public Prop::cProp
    {
    public:
        // Prototype interface from RuffKing; CD2 slot 5 at 0x8245B000. Instance fields are not modelled.
        // CD2's MakeNew (0x8245AEC0) allocates 0x500, calls cPropPrototype's constructor and then stores this class's
        // vptrs and zero at 0x4F0: the constructor is inline. RuffKing: 1280 bytes, m_nInteractionAnimID at 0x4F0.
        class cMissionCriticalPropPrototype : public Prop::cProp::cPropPrototype
        {
        public:
            __forceinline cMissionCriticalPropPrototype(const RWS::CAttributePacket &packet)
                : Prop::cProp::cPropPrototype(packet), m_nInteractionAnimID(0) {}
            virtual Fun_Runtime::RetVal Init(const RWS::CAttributePacket &);

            unsigned int m_nInteractionAnimID;

            CD2_LAYOUT_CHECKS(cMissionCriticalPropPrototype,
                CD2_SIZE(cMissionCriticalPropPrototype, 0x500)
                CD2_OFFSET(cMissionCriticalPropPrototype, m_nInteractionAnimID, 0x4F0))
        };

        // CD2 spawning initializer 0x82F873A0 names placement factory 0x8245af48.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        // CD2 0x8245B0C8: the placement factory (0x8245AF48) calls it out of line with the prototype.
        cMissionCriticalProp(GOM::cObjectPrototype *);
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        static const Fun_Runtime::cClass *ms_pcMissionCriticalPropClass;
        // CD2 registered-class table 0x8210350C points at 0x8245AE50/0x8245AE60; bodies are outside this split.
        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;
        // CD2 0x8245B1E0.
        virtual ~cMissionCriticalProp();
        virtual Fun_Runtime::RetVal Init(const GOM::cSpawner *);
    private:
        // RuffKing name; CD2 constructor 0x8245B0C8 stores one at +0xE30.
        bool m_bInteractable;
        CD2_LAYOUT_CHECKS(cMissionCriticalProp,
            CD2_SIZE(cMissionCriticalProp, 0xE40)
            CD2_OFFSET(cMissionCriticalProp, m_bInteractable, 0xE30))
    };
}

#endif // AI_CMISSIONCRITICALPROP_H
