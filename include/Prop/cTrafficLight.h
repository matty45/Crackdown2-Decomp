// Prop::cTrafficLight (CD2 layout, 0xE60 bytes) and its prototype (0x510 bytes). Evidence:
// - Sizes: the registrar (0x82FFC358) registers cTrafficLight with size 0xE60; the prototype's MakeNew (0x827473C0)
//   allocates 0x510 bytes and calls cPropPrototype's constructor (0x8272D390), then zeroes 0x4F0 and sets the byte at
//   0x500 to 0xFF.
// - Fields (RuffKing names, CD2 offsets; RuffKing's are 0x70 higher, its cProp being 0xEA0 bytes): the constructor
//   (0x82747470) stores a doubleword at 0xE30 (m_iTrafficControlEdgeID), words at 0xE38 and 0xE3C (the colours) and
//   bytes at 0xE40-0xE42. UpdateRenderMatrix (0x827478F8) compares the two colours as signed words (an enum), tests the
//   three bytes and copies 0xE3C to 0xE38. The words from 0xE44 are one light per light index (AddLight reads 0xE44 +
//   index times 4); they and the rest up to 0xE60 are not modelled yet.
// - The prototype's word at 0x4F0 is the number of lights: unsigned (cmplw against the loop index), read through
//   m_pPrototype (0x44). AddLight picks one of the words at 0x4F4, 0x4F8 and 0x4FC by colour; not modelled yet.
// - Primary vtable 0x8200F530: UpdateRenderMatrix is slot 26 (see Prop/cProp.h). Only the functions matched so far are
//   declared.
// - The colours are AI::cJunctionNodeController::eSignalColour (AI/cJunctionNodeController.h).
#ifndef PROP_CTRAFFICLIGHT_H
#define PROP_CTRAFFICLIGHT_H

#include "cd2/layout.h"
#include "Prop/cProp.h"
#include "AI/cJunctionNodeController.h"

namespace Prop
{
    class cTrafficLight : public cProp
    {
    public:
        class cTrafficLightPrototype : public cProp::cPropPrototype
        {
        public:
            unsigned int m_nNumLights;               // 0x4F0
        private:
            unsigned char m_pad4F4[0x510 - 0x4F4];

        public:
            CD2_LAYOUT_CHECKS(cTrafficLightPrototype,
                CD2_SIZE(cTrafficLightPrototype, 0x510)
                CD2_OFFSET(cTrafficLightPrototype, m_nNumLights, 0x4F0))
        };

    protected:
        long long m_iTrafficControlEdgeID;                               // 0xE30
        AI::cJunctionNodeController::eSignalColour m_eCurrentColour;     // 0xE38
        AI::cJunctionNodeController::eSignalColour m_eNewColour;         // 0xE3C
        bool m_bLightActive;                                             // 0xE40
        bool m_bFirstRender;                                             // 0xE41
        bool m_bIsBroken;                                                // 0xE42
    private:
        unsigned char m_padE43[0xE60 - 0xE43];

    public:
        virtual void UpdateRenderMatrix();                               // slot 26, 0x827478F8

    protected:
        bool AddLight(int, AI::cJunctionNodeController::eSignalColour);  // 0x82747998

        CD2_LAYOUT_CHECKS(cTrafficLight,
            CD2_SIZE(cTrafficLight, 0xE60)
            CD2_OFFSET(cTrafficLight, m_iTrafficControlEdgeID, 0xE30)
            CD2_OFFSET(cTrafficLight, m_eCurrentColour, 0xE38)
            CD2_OFFSET(cTrafficLight, m_eNewColour, 0xE3C)
            CD2_OFFSET(cTrafficLight, m_bLightActive, 0xE40)
            CD2_OFFSET(cTrafficLight, m_bFirstRender, 0xE41)
            CD2_OFFSET(cTrafficLight, m_bIsBroken, 0xE42))
    };
}

#endif // PROP_CTRAFFICLIGHT_H
