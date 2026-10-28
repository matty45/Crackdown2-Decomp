// Fun_Runtime::cClass: runtime class descriptor behind the RetClass/IsA/StaticCreateClass virtuals of game classes.
// Layout and names from the RuffKing PDB; size 0x5C, ID at 0, parent bit set at 0x2D and bit ID at 0x58 confirmed in
// CD2 by VFX::cAmbientVFXSpawner::IsA and VFX::cRopes::IsA (both byte-exact). IsA and HasAncestor are inline in CD2,
// and this short-circuit form is what produces CD2's branchy li 0 / li 1 bool.
#ifndef FUN_RUNTIME_CLASS_H
#define FUN_RUNTIME_CLASS_H

#include "cd2/layout.h"

namespace Fun_Runtime
{
    // Only CONST_INT_0 and CONST_INT_1 are confirmed in CD2 (HasAncestor); the rest is RuffKing's layout.
    struct tGlobalConstants
    {
        const int CONST_INT_0;
        const int CONST_INT_1;
        const int CONST_INT_2;
        const int CONST_INT_100;
        const float CONST_FLOAT_0;
        const float CONST_FLOAT_1;
        const float CONST_FLOAT_2;
        const float CONST_FLOAT_100;
        const float CONST_FLOAT_PI;
        const float CONST_FLOAT_0d000001;
        const float CONST_FLOAT_0d25;
    };
    extern const tGlobalConstants g_GlobalConstants;

    class cClass
    {
    private:
        unsigned int m_nID;
        const char *m_sName;
        unsigned int m_nSize;
        unsigned char m_lParents[0x10];  // cVector<cClass *, cAllocator<...>> in RuffKing; opaque here
        unsigned char m_lChildren[0x10];
        bool m_bBitParentsCalced;
        unsigned char m_bitIDsForParents[40];
        int m_nBitID;

    public:
        cClass(unsigned int, const char *, unsigned int);
        bool HasAncestor(const cClass &c) const
        {
            return ((g_GlobalConstants.CONST_INT_1 << (c.m_nBitID & 7)) & m_bitIDsForParents[c.m_nBitID >> 3])
                != g_GlobalConstants.CONST_INT_0;
        }
        bool IsA(const cClass &c) const
        {
            return c.m_nID == m_nID || HasAncestor(c);
        }

        CD2_LAYOUT_CHECKS(cClass,
            CD2_SIZE(cClass, 0x5C)
            CD2_OFFSET(cClass, m_bitIDsForParents, 0x2D)
            CD2_OFFSET(cClass, m_nBitID, 0x58))
    };

    // The RetClass/IsA interface of game objects (cNonGameBase, at 0x30). Both are pure in CD2's own vtable
    // (0x820FF0CC) and every game class's copy holds its RetClass and IsA. RuffKing's and Burn's class is the vptr
    // alone in CD2 too (4 bytes). The flag after cScriptHost's registered-class subobject belongs to cScriptHost;
    // it pads that complete base to 0x1C. Its next sibling in cNonGameBase starts at 0x38.
    class cRegisteredClass
    {
    public:
        virtual const cClass &RetClass() const = 0;
        virtual bool IsA(const cClass &) const = 0;
    private:


    public:
        CD2_LAYOUT_CHECKS(cRegisteredClass,
            CD2_SIZE(cRegisteredClass, 0x4))
    };
}

#endif // FUN_RUNTIME_CLASS_H
