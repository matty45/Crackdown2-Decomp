// STAND-IN: pointer-only Havok reference-count interface. RuffKing declares removeReference() const;
// CD2 0x82BD2300 decrements the count at +6 and invokes the deleting virtual when it reaches zero.
// Reference base and reference-count storage are now modelled; the CD2 removal body confirms offsets +4/+6.
#ifndef HAVOK_HKREFERENCEDOBJECT_H
#define HAVOK_HKREFERENCEDOBJECT_H
#include "Havok/hkBaseObject.h"
class hkStatisticsCollector;
class hkReferencedObject : public hkBaseObject
{
public:
    virtual ~hkReferencedObject();
    virtual void calcStatistics(hkStatisticsCollector *) const;
    void removeReference() const;
protected:
    unsigned short m_memSizeAndFlags;
    short m_referenceCount;
    CD2_LAYOUT_CHECKS(hkReferencedObject,
        CD2_SIZE(hkReferencedObject, 8)
        CD2_OFFSET(hkReferencedObject, m_memSizeAndFlags, 4)
        CD2_OFFSET(hkReferencedObject, m_referenceCount, 6))
};
#endif
