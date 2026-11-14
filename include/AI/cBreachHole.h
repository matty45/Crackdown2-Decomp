#ifndef AI_CBREACHHOLE_H
#define AI_CBREACHHOLE_H

#include "rws/systemcommands.h"
#include "rws/attributes.h"
#include "rws/eventhandler.h"
#include "rws/dynamicallocationpolicy.h"
#include "fun_runtime/class.h"
#include "rws/attributes.h"
#include "cd2/layout.h"

namespace AI
{
    // CD2's table (0x820044D8) has RWS::CAttributeHandler's eleven slots, then RetClass, IsA, RetClassName and Destruct in slots
    // 11 to 14, as RuffKing declares the class: RWS::CSystemCommands, CAttributeHandler, CEventHandler and DynamicAllocationPolicy.
    class cBreachHole : public RWS::CSystemCommands, public RWS::CAttributeHandler, public RWS::CEventHandler,
        public RWS::DynamicAllocationPolicy
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcBreachHoleClass;

        cBreachHole();
        // Out of line (CD2 0x8246EB40): the deleting wrapper calls it.
        virtual ~cBreachHole();
        static RWS::CAttributeHandler *MakeNew(const RWS::CAttributePacket &packet, bool);

        virtual const Fun_Runtime::cClass &RetClass() const;
        virtual bool IsA(const Fun_Runtime::cClass &) const;
        virtual const char *RetClassName() const;
        virtual void Destruct();
        // RWS::CEventHandler's pure virtual (RuffKing declares the override).
        virtual void HandleEvents(RWS::CMsg &);
        // CD2: cBreachHole's own virtuals. Each slot below holds, in this class's CD2 vtable (and its derived classes'), an
        // address its base's table does not hold there, so the class overrides it; names and signatures are the bases'.
    public:
        virtual void HandleAttributes(RWS::CAttributePacket const &); // 1: 0x8246EC00
        // CD2's table 0x820044D8 has 20 slots; 15..19 are RuffKing's own virtuals in its order (cBreach.h vtable
        // offsets 60..76).
        virtual void HandleSystemCommands(const RWS::CAttributePacket &attr);   // 15: 0x8246F4D0
        virtual void TickUpdate(float dT, bool bAlternateBreach);              // 16: 0x8246F598
        virtual void TryKillAllSpawned();                                       // 17: 0x82470220

        // RuffKing's states (cBreach.h); CD2's StartDeActivateBreachHole (0x8246F990) tests eBHS_Closed and requests
        // eBHS_Closing.
        enum eBreachHoleState
        {
            eBHS_Inactive = 0,
            eBHS_Opening,
            eBHS_Open,
            eBHS_Closing,
            eBHS_Closed,
            eBHS_Destroyed,
            eBHS_Standby,
            eBHS_Suspended,
            eBS_NumStates,
            eBS_Invalid = eBS_NumStates
        };
        void StartDeActivateBreachHole();
        void ChangeState(eBreachHoleState eBHSNewState);       // CD2 0x8246FB40
        virtual void ExitState(eBreachHoleState eBHSNewState);                  // 18: 0x824700B8
        virtual void EnterState(eBreachHoleState eBHSNewState);                 // 19: 0x8246FBB0

    private:
        // CD2's registrar and MakeNew (0x8246E758) give 0x1C0 bytes; RuffKing's class (cBreach.h) is 0x170. The fields
        // below have RuffKing's names and offsets, which StartDeActivateBreachHole confirms; the rest is not modelled.
        eBreachHoleState m_eBreachHoleState;                    // 0x20
        unsigned char m_unmodelled24[0x5C - 0x24];
        float m_fOpenTimer;                                     // 0x5C
        float m_fCloseTimer;                                    // 0x60
        float m_fCurrentTimer;                                  // 0x64
        float m_fSuspendTimer;                                  // 0x68
        unsigned char m_unmodelled6C[0xA4 - 0x6C];
        cBreachHole *m_pAlternateBreach;                        // 0xA4
        unsigned char m_unmodelledA8[0x1C0 - 0xA8];
        CD2_LAYOUT_CHECKS(cBreachHole,
            CD2_SIZE(cBreachHole, 0x1C0)
            CD2_OFFSET(cBreachHole, m_eBreachHoleState, 0x20)
            CD2_OFFSET(cBreachHole, m_fOpenTimer, 0x5C)
            CD2_OFFSET(cBreachHole, m_fCurrentTimer, 0x64)
            CD2_OFFSET(cBreachHole, m_pAlternateBreach, 0xA4))
    };
}

#endif

