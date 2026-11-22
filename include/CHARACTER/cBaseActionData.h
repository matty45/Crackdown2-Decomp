// Reference cBaseActionData layout. CD2 ResetData 0x823ACE10 clears the
// force flag at +4, action/trigger/flag bytes at +0x19..+0x1B, and unlinks
// the safe pointer at +8. Its table 0x82109968 has destructor/ResetData slots.
// Ledge data starts its own trigger enum at +0x1C, confirming the base size.
#pragma once
#include "fun_runtime/safedeletablepointer.h"
#include "cd2/layout.h"

class cGameBase;
namespace CHARACTER
{
    class cBaseActionData
    {
    public:
        cBaseActionData();
        virtual ~cBaseActionData();
        virtual void ResetData();
        unsigned char m_bForce : 1;
    protected:
        Fun_Runtime::cSafeDeletablePointer<cGameBase> m_pGameBaseObject;
        unsigned char m_nDataType;
        unsigned char m_nActionType;
        unsigned char m_nTrigger;
        unsigned char m_bImmediate : 1;
        unsigned char m_bPermitedToBeSkipped : 1;

        CD2_LAYOUT_CHECKS(cBaseActionData,
            CD2_SIZE(cBaseActionData, 0x1C)
            CD2_OFFSET(cBaseActionData, m_pGameBaseObject, 8)
            CD2_OFFSET(cBaseActionData, m_nDataType, 0x18)
            CD2_OFFSET(cBaseActionData, m_nActionType, 0x19)
            CD2_OFFSET(cBaseActionData, m_nTrigger, 0x1A))
    };
}
