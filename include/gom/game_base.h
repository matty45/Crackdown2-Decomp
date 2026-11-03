#include "fun_runtime/class.h"
// STAND-IN: Burn/RuffKing base order; CD2 cBody debug interface starts at 0x120.
#ifndef CD2_GOM_GAME_BASE_H
#define CD2_GOM_GAME_BASE_H
#include "gom/non_game_base.h"
#include "rws/systemcommands.h"
__declspec(align(16)) class cGameBase : public RWS::CSystemCommands, public cNonGameBase
{
    public:
        // CD2 0x82650268 creates the named runtime descriptor.
        static Fun_Runtime::cClass &StaticCreateClass();

public:
    virtual ~cGameBase();
private:
    unsigned char m_unknown7C[0x120 - 0x7C];
    CD2_LAYOUT_CHECKS(cGameBase, CD2_SIZE(cGameBase, 0x120))
};
#endif
