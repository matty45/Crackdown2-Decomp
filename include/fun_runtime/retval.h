// Fun_Runtime::RetVal: result code returned by value (one int; RuffKing and Burn PDBs agree), and the Ret_OK/Ret_FAIL
// constants. The constants are const objects at namespace scope, so every source file has its own copies (RuffKing has
// 804 copies of Ret_OK). CD2 matches this exactly: Ret_OK (0) sits in each file's .bss, Ret_FAIL (-1) in .data, nothing
// initializes them at run time, and code loads them (cHelicopterController.cpp: Ret_OK at 0x8385253C, Ret_FAIL at
// 0x8320731C; the vehicle controller's file has its own Ret_OK at 0x83852490). The compiler produces the same: static
// initialization and loads, no folding.
#ifndef FUN_RUNTIME_RETVAL_H
#define FUN_RUNTIME_RETVAL_H

#include "cd2/layout.h"

namespace Fun_Runtime
{
    class RetVal
    {
    private:
        int m_nVal;

    public:
        RetVal(int n) : m_nVal(n) {}
        RetVal() {}
        int GetVal() const { return m_nVal; }
        operator int() const { return m_nVal; }

        CD2_LAYOUT_CHECKS(RetVal,
            CD2_SIZE(RetVal, 0x4))
    };
}

const Fun_Runtime::RetVal Ret_OK(0);
const Fun_Runtime::RetVal Ret_FAIL(-1);

#endif // FUN_RUNTIME_RETVAL_H
