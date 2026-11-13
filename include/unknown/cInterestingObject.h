// unknown::cInterestingObject: CD2 stand-in. Constructor 0x82453E98 initializes
// cScriptHost at +0, including its registered-class interface at +0x14, then its
// own fields at +0x1C..0x3C. The descriptor establishes size 0x40.
// Its StaticCreateClass is CD2 0x82454A88 (names the class "cInterestingObject"); derived classes register it as their parent.
#ifndef UNKNOWN_CINTERESTINGOBJECT_H
#define UNKNOWN_CINTERESTINGOBJECT_H

#include "fun_runtime/class.h"
#include "fun_runtime/scripthost.h"

namespace unknown
{
    class cInterestingObject : public Fun_Runtime::cScriptHost
    {
    public:
        static Fun_Runtime::cClass &StaticCreateClass();
        static const Fun_Runtime::cClass *ms_pcInterestingObjectClass;
        // Script methods (names from CD2's registration at 0x82454EA4..0x824552CC); each field is named after the
        // script method that reads or writes it.
        unsigned char RetBasicReaction();
        float RetMaximumDuration();
        float RetMinimumDuration();
        bool IsDangerous();
        void SetType(int);
        void SetMaxReactingChars(unsigned short);
        void IncrementReactingCharCount();
        void DecrementReactingCharCount();
        void SetBasicReaction(unsigned char);
        void SetMaximumDuration(float);
        void SetMinimumDuration(float);
        void SetPriority(unsigned char);
        void SetDangerous(bool);
    private:
        unsigned char m_unmodelled1C[0x20 - 0x1C];
        int m_nType;
        unsigned char m_unmodelled24[0x2C - 0x24];
        float m_fMaximumDuration;
        float m_fMinimumDuration;
        unsigned short m_nReactingCharCount;
        unsigned short m_nMaxReactingChars;
        unsigned char m_unmodelled38[0x3A - 0x38];
        unsigned char m_eBasicReaction; // eBasicReactions
        unsigned char m_ePriority;      // eNotifyPriority
        bool m_bDangerous;
        unsigned char m_unmodelled3D[0x40 - 0x3D];
        CD2_LAYOUT_CHECKS(cInterestingObject,
            CD2_SIZE(cInterestingObject, 0x40)
            CD2_OFFSET(cInterestingObject, m_nType, 0x20)
            CD2_OFFSET(cInterestingObject, m_fMaximumDuration, 0x2C)
            CD2_OFFSET(cInterestingObject, m_fMinimumDuration, 0x30)
            CD2_OFFSET(cInterestingObject, m_nReactingCharCount, 0x34)
            CD2_OFFSET(cInterestingObject, m_nMaxReactingChars, 0x36)
            CD2_OFFSET(cInterestingObject, m_eBasicReaction, 0x3A)
            CD2_OFFSET(cInterestingObject, m_ePriority, 0x3B)
            CD2_OFFSET(cInterestingObject, m_bDangerous, 0x3C))
    };
}

#endif // UNKNOWN_CINTERESTINGOBJECT_H
