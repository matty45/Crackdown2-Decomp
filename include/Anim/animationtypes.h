// Enum names and values from RuffKing's animation interface.
#ifndef ANIM_ANIMATIONTYPES_H
#define ANIM_ANIMATIONTYPES_H
namespace Anim
{
    enum eEndBehavior { eEB_Loop = 0, eEB_Hold, eEB_Max };
    enum eActionType { eAT_Invalid = -1, eAT_Main = 0, eAT_Secondary, eAT_Num, eAT_Bth };
}
#endif
