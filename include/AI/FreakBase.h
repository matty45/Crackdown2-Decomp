#include "rws/attributes.h"
// AI::FreakBase (Crackdown 2): STAND-IN for the class name only. Base AI::NPCBehaviourSM, as in RuffKing's header;
// RetClassName (0x824ABC68) is slot 11 of the vtable at 0x82109378, as cNonGameBase's RetClassName.
#ifndef AI_FREAKBASE_H
#define AI_FREAKBASE_H

#include "AI/cChaseBehaviour.h"
#include "gom/object_prototype.h"
#include "cd2/layout.h"

namespace AI
{
    // RuffKing: AI::FreakPrototype : NPCBehaviourPrototype, 176 bytes. CD2's FreakBase::MakeNew (0x824ABC10) allocates
    // 0xB0 and calls this constructor (0x824B0B78), which calls NPCBehaviourPrototype's (0x824A8608).
    class FreakPrototype : public NPCBehaviourPrototype
    {
    public:
        FreakPrototype(const RWS::CAttributePacket &);

    private:
        unsigned char m_unmodelled90[0xB0 - 0x90];

        CD2_LAYOUT_CHECKS(FreakPrototype,
            CD2_SIZE(FreakPrototype, 0xB0))
    };

    class FreakBase : public AI::NPCBehaviourSM
    {
    public:
        // CD2 constructor installs table 0x82109378, with 179 primary slots. Names/signatures of these slots remain unrecovered.
        virtual void Slot101();
        virtual void V102();
        virtual void Slot103();
        virtual void V104();
        virtual void Slot105();
        virtual void V106();
        virtual void V107();
        virtual void V108();
        virtual void Slot109();
        virtual void Slot110();
        virtual void V111(float dt);
        virtual void Slot112();
        virtual void Slot113();
        virtual void Slot114();
        virtual NPCTarget *GetTarget();
        virtual int GetTargetId();
        virtual void V117();
        virtual void V118();
        virtual void vf119(); // primary slot 119
        virtual void vf120(); // primary slot 120
        virtual void vf121(); // primary slot 121
        virtual void vf122(); // primary slot 122
        virtual void vf123(); // primary slot 123
        virtual void vf124(); // primary slot 124
        virtual void vf125(); // primary slot 125
        virtual void vf126(); // primary slot 126
        virtual void vf127(); // primary slot 127
        virtual void vf128(); // primary slot 128
        virtual void vf129(); // primary slot 129
        virtual void vf130(); // primary slot 130
        virtual void vf131(); // primary slot 131
        virtual void vf132(); // primary slot 132
        virtual void vf133(); // primary slot 133
        virtual void vf134(); // primary slot 134
        virtual void vf135(); // primary slot 135
        virtual void vf136(); // primary slot 136
        virtual void vf137(); // primary slot 137
        virtual void vf138(); // primary slot 138
        virtual void vf139(); // primary slot 139
        virtual void vf140(); // primary slot 140
        virtual void vf141(); // primary slot 141
        virtual void vf142(); // primary slot 142
        virtual void vf143(); // primary slot 143
        virtual void vf144(); // primary slot 144
        virtual void vf145(); // primary slot 145
        virtual void vf146(); // primary slot 146
        virtual void vf147(); // primary slot 147
        virtual void vf148(); // primary slot 148
        virtual void vf149(); // primary slot 149
        virtual void vf150(); // primary slot 150
        virtual void vf151(); // primary slot 151
        virtual void vf152(); // primary slot 152
        virtual void vf153(); // primary slot 153
        virtual void vf154(); // primary slot 154
        virtual void vf155(); // primary slot 155
        virtual void vf156(); // primary slot 156
        virtual void vf157(); // primary slot 157
        virtual void vf158(); // primary slot 158
        virtual void vf159(); // primary slot 159
        virtual void vf160(); // primary slot 160
        virtual void vf161(); // primary slot 161
        virtual void vf162(); // primary slot 162
        virtual void vf163(); // primary slot 163
        virtual void vf164(); // primary slot 164
        virtual void vf165(); // primary slot 165
        virtual void vf166(); // primary slot 166
        virtual void vf167(); // primary slot 167
        virtual void vf168(); // primary slot 168
        virtual void vf169(); // primary slot 169
        virtual void vf170(); // primary slot 170
        virtual void vf171(); // primary slot 171
        virtual void vf172(); // primary slot 172
        virtual void vf173(); // primary slot 173
        virtual void vf174(); // primary slot 174
        virtual void vf175(); // primary slot 175
        virtual void vf176(); // primary slot 176
        virtual void vf177(); // primary slot 177
        virtual void vf178(); // primary slot 178

        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &, bool);
        FreakBase();
        static RWS::CAttributeHandler *SpawnFromPrototype(GOM::cObjectPrototype *, void *memory);
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        static const Fun_Runtime::cClass *ms_pFreakBaseClass;
        virtual const Fun_Runtime::cClass &RetClass() const;
        static Fun_Runtime::cClass &StaticCreateClass();
        virtual const char *RetClassName() const;

    private:
        unsigned char m_unmodelledD0[0x120 - 0xD0];

        // CD2: FreakBase's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual unsigned char GetStateReplicationInfo() const; // 89: 0x824BAD88
    private:
        CD2_LAYOUT_CHECKS(FreakBase, CD2_SIZE(FreakBase, 0x120))

    public:
        // CD2 table 0x82109378 differs from NPCBehaviourSM at these inherited slots.
        virtual void OnEnter(); // slot 68: 0x824ABED0
        virtual void OnExit(); // slot 69: 0x824AC120
        virtual void Slot71(); // slot 71: 0x824AD168
        virtual void OnEvent74(NPCTarget *t); // slot 74: 0x824ADAA0
        virtual void OnEvent75(NPCTarget *t); // slot 75: 0x824ADBF0
        virtual void Slot79(); // slot 79: 0x824ADC70
        virtual void Slot80(unsigned char nEventType, unsigned char nEventSubType, unsigned char nEvent); // slot 80: 0x824AD948
        virtual void Slot83(); // slot 83: 0x824ADA20
        virtual void SetReactResupplyPoint(const Fun_Runtime::Vec3 &, const Fun_Runtime::Vec3 &); // slot 85: 0x824AD910
        virtual void Slot86(); // slot 86: 0x824ABCA0
        virtual void Slot95(); // slot 95: 0x824ABC90
        virtual void GetState(int n); // slot 100: 0x824AC4B0
    };
}

#endif // AI_FREAKBASE_H
