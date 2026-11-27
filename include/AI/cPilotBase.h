// CD2 constructor 0x824D32E0 confirms this behaviour-base chain; remaining instance fields are incomplete.
#include "AI/NPCBehaviour.h"
#include "gom/object_prototype.h"
#ifndef AI_CPILOTBASE_H
#define AI_CPILOTBASE_H

#include "gom/non_game_base.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"

namespace AI
{
    class cPilotBase : public AI::NPCBehaviour
    {
    public:
        // CD2 constructor 0x824D32E0 installs 115-slot table 0x8200B3B8. Names/signatures of these slots remain unrecovered.
        // RuffKing's first own virtual (its 19 slots from OnEnterCold are CD2's 96..114); OnEnter calls it.
        virtual void OnEnterCold(); // primary slot 96
        virtual void vf97(); // primary slot 97
        virtual void vf98(); // primary slot 98
        virtual void vf99(); // primary slot 99
        virtual void vf100(); // primary slot 100
        virtual void vf101(); // primary slot 101
        virtual void vf102(); // primary slot 102
        virtual void vf103(); // primary slot 103
        virtual void vf104(); // primary slot 104
        virtual void vf105(); // primary slot 105
        virtual void vf106(); // primary slot 106
        virtual void vf107(); // primary slot 107
        virtual void vf108(); // primary slot 108
        virtual void vf109(); // primary slot 109
        virtual void vf110(); // primary slot 110
        virtual void vf111(); // primary slot 111
        virtual void vf112(); // primary slot 112
        virtual void vf113(); // primary slot 113
        virtual void vf114(); // primary slot 114

        // CD2 spawning initializer 0x82F9BE38 names placement factory 0x824d31b0.
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *);
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcPilotBaseClass;

        cPilotBase();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;

    private:
    protected:
        // RuffKing's names and order (its +0x100/+0x101): GetStateReplicationInfo (0x824D42A8) returns the first,
        // OnEnter (0x824D3410) sets the second. 0x140 is the size its registrar and descriptor give.
        unsigned char m_nState;                 // 0xC0
        unsigned char m_nMigratedState;         // 0xC1
    private:
        unsigned char m_unmodelledC2[0x140 - 0xC2];

        // CD2: cPilotBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void Slot2(); // cSafeDeletable 2: 0x824D3DE0
    private:
        CD2_LAYOUT_CHECKS(cPilotBase,
            CD2_SIZE(cPilotBase, 0x140)
            CD2_OFFSET(cPilotBase, m_nState, 0xC0)
            CD2_OFFSET(cPilotBase, m_nMigratedState, 0xC1))

    public:
        // CD2 table 0x8200B3B8 differs from NPCBehaviour at these inherited slots.
        // Slot 68 (0x824D3410). Inline: cTrainingHeliPilot's OnEnter (0x824D5508) expands it.
        virtual void OnEnter()
        {
            OnEnterCold();
            m_nMigratedState = 1;
        }
        virtual void OnExit(); // slot 69: 0x824D3590
        virtual void Update(float fDeltaTime); // slot 71: 0x822026C8
        virtual void OnEnterReplicatedState(unsigned char); // slot 72: 0x824A7E70
        virtual void OnAttacked(CHARACTER::cCharacter *, const Fun_Runtime::Vec3 &, cAIEvent *); // slot 73: 0x824D3610
        virtual void OnDied(CHARACTER::cCharacter *, cAIEvent *); // slot 79: 0x824C7980
        virtual unsigned char GetStateReplicationInfo() const; // slot 89: 0x824D42A8
        virtual bool ShouldLockVehicleOwnership() const; // slot 94: 0x827E56A8
    };
}

#endif

