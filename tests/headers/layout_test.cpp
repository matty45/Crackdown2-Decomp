// Compile-only test: every curated header must compile with the CD2 compiler and pass its layout checks.
// Build: tools/headers/check_headers.ps1
#include "rws/attributes.h"
#include "gom/non_game_base.h"   // with rws/eventhandler.h, fun_runtime/safedeletable.h, retval.h, class.h,
                                 // network/netrole.h and gom/object_prototype.h

#ifdef CD2_SELFTEST_EXPECT_FAILURE
// Proves the checks actually fire: this class is 8 bytes, so a 0xC size check must fail with C2118.
struct cd2_selftest
{
    int a, b;
    CD2_LAYOUT_CHECKS(cd2_selftest,
        CD2_SIZE(cd2_selftest, 0xC))
};
#endif
