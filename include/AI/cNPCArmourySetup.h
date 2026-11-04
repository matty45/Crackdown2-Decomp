// STAND-IN: RuffKing exported.h names this global, empty attribute-schema base.
// PedestrianGuard and CellGuard inherit it alongside their behaviour base.
// It has no virtuals or instance fields (reference sizeof == 1).
#ifndef AI_CNPCARMOURYSETUP_H
#define AI_CNPCARMOURYSETUP_H
#include "cd2/layout.h"
class cNPCArmourySetup
{
public:
    static const char *pcNPCArmourySetupClassID;
    static const char *RetRWSClassName();
    CD2_LAYOUT_CHECKS(cNPCArmourySetup, CD2_SIZE(cNPCArmourySetup, 1))
};
#endif
